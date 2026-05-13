/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtx_kernel.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:00:00 by rbetz             #+#    #+#             */
/*   Updated: 2026/05/13 10:00:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtx.h"
#include <math.h>
#include <float.h>

#define GPU_T_MIN 0.001
#define GPU_T_MAX DBL_MAX

/* Enum mirrors t_type from miniRT.h */
#define GPU_CAM    0
#define GPU_LIGHT  1
#define GPU_AMBI   2
#define GPU_SPHERE 3
#define GPU_CYL    4
#define GPU_PLN    5
#define GPU_RES    6
#define GPU_CIRCLE 7
#define GPU_RECT   8
#define GPU_SQUA   9

/* ---- Vector math (device inline) ---- */

struct d_vec { double x, y, z; };

__device__ inline d_vec make_vec(double x, double y, double z)
{
	d_vec v;
	v.x = x; v.y = y; v.z = z;
	return v;
}

__device__ inline d_vec vec_add(d_vec a, d_vec b)
{
	return make_vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

__device__ inline d_vec vec_sub(d_vec a, d_vec b)
{
	return make_vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

__device__ inline d_vec vec_mul(d_vec a, d_vec b)
{
	return make_vec(a.x * b.x, a.y * b.y, a.z * b.z);
}

__device__ inline d_vec vec_scale(d_vec v, double s)
{
	return make_vec(v.x * s, v.y * s, v.z * s);
}

__device__ inline d_vec vec_div(d_vec v, double s)
{
	return make_vec(v.x / s, v.y / s, v.z / s);
}

__device__ inline double vec_dot(d_vec a, d_vec b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

__device__ inline d_vec vec_cross(d_vec a, d_vec b)
{
	return make_vec(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

__device__ inline double vec_length_sq(d_vec v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

__device__ inline double vec_length(d_vec v)
{
	return sqrt(vec_length_sq(v));
}

__device__ inline d_vec vec_normalize(d_vec v)
{
	double len = vec_length(v);
	if (len == 0.0)
		return v;
	return vec_div(v, len);
}

__device__ inline d_vec vec_abs(d_vec v)
{
	return make_vec(fabs(v.x), fabs(v.y), fabs(v.z));
}

__device__ inline d_vec vec_from_arr(const double *a)
{
	return make_vec(a[0], a[1], a[2]);
}

/* ---- Random number generation (xorshift per-thread) ---- */

__device__ inline int gpu_xorshift(int seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

__device__ inline double gpu_random_double(int seed)
{
	double r = (double)seed / (double)((double)2147483647 + 1.0);
	if (r < 0.0)
		r = -r;
	return r;
}

__device__ d_vec gpu_random_vector(int seed)
{
	double x, y, z;
	seed = gpu_xorshift(seed);
	x = gpu_random_double(seed);
	seed = gpu_xorshift(seed);
	y = gpu_random_double(seed);
	seed = gpu_xorshift(seed);
	z = gpu_random_double(seed);
	return make_vec(x * 2.0 - 1.0, y * 2.0 - 1.0, z * 2.0 - 1.0);
}

__device__ d_vec gpu_random_in_hemisphere(int *seed, d_vec normal)
{
	d_vec v;
	int attempts = 0;
	double len_sq;

	do {
		*seed = gpu_xorshift(*seed);
		v = gpu_random_vector(*seed);
		len_sq = vec_length_sq(v);
		attempts++;
	} while ((len_sq > 1.0 || len_sq < 0.001) && attempts < 64);
	v = vec_normalize(v);
	if (vec_dot(v, normal) < 0.0)
		v = vec_scale(v, -1.0);
	return v;
}

/* ---- Ray structure ---- */

struct d_ray
{
	d_vec	origin;
	d_vec	direction;
	double	closest_t;
	int		closest_idx;
	d_vec	normal;
};

/* ---- Point at t ---- */

__device__ inline d_vec point_at_t(d_ray ray, double t)
{
	return vec_add(ray.origin, vec_scale(ray.direction, t));
}

__device__ inline bool front_facing_gpu(d_vec ray_dir, d_vec face_normal)
{
	return vec_dot(ray_dir, face_normal) < 0.0;
}

/* ---- Intersection tests ---- */

__device__ bool gpu_hit_sphere(d_ray *ray, t_gpu_obj *obj, int idx)
{
	d_vec	oc = vec_sub(ray->origin, vec_from_arr(obj->origin));
	double	len_dir = vec_length(ray->direction);
	double	a = len_dir * len_dir;
	double	b = vec_dot(oc, ray->direction);
	double	len_oc = vec_length(oc);
	double	disc = b * b - (a * len_oc * len_oc - obj->radius * obj->radius);

	if (disc <= 0.0)
		return false;
	disc = sqrt(disc);
	double t = (-b - disc) / a;
	if (t < GPU_T_MIN || t > GPU_T_MAX)
	{
		t = (-b + disc) / a;
		if (t < GPU_T_MIN || t > GPU_T_MAX)
			return false;
	}
	if (t >= ray->closest_t)
		return false;
	ray->closest_t = t;
	ray->closest_idx = idx;
	d_vec hit_pt = point_at_t(*ray, t);
	ray->normal = vec_div(vec_sub(hit_pt, vec_from_arr(obj->origin)), obj->radius);
	return true;
}

__device__ bool gpu_hit_plane(d_ray *ray, t_gpu_obj *obj, int idx)
{
	d_vec obj_n = vec_from_arr(obj->vector);
	d_vec obj_o = vec_from_arr(obj->origin);
	double ortho = vec_dot(obj_n, ray->direction);

	if (ortho == 0.0)
		return false;
	double pln_d = vec_dot(obj_o, obj_n);
	double dis = vec_dot(obj_n, ray->origin);
	double t = (pln_d - dis) / ortho;
	if (t < GPU_T_MIN || t > GPU_T_MAX)
		return false;
	if (t >= ray->closest_t)
		return false;
	ray->closest_idx = idx;
	ray->closest_t = t;
	ray->normal = obj_n;
	return true;
}

__device__ bool gpu_hit_cylinder(d_ray *ray, t_gpu_obj *obj, int idx)
{
	d_vec obj_vec = vec_from_arr(obj->vector);
	d_vec obj_orig = vec_from_arr(obj->origin);
	d_vec d = vec_cross(ray->direction, obj_vec);
	d_vec cros = vec_cross(vec_sub(ray->origin, obj_orig), obj_vec);

	double a0 = vec_length_sq(d);
	double a1 = 2.0 * vec_dot(d, cros);
	double a2 = vec_length_sq(cros) - (obj->radius * obj->radius);

	if (a0 == 0.0)
		return false;
	double disc = a1 * a1 - 4.0 * a0 * a2;
	if (disc < 0.0)
		return false;
	disc = sqrt(disc);
	double t0 = (-a1 - disc) / (2.0 * a0);
	double t1 = (-a1 + disc) / (2.0 * a0);

	/* Pick smallest valid t */
	double val = GPU_T_MAX;
	if (t0 > GPU_T_MIN && t0 < GPU_T_MAX)
		val = t0;
	if (t1 > GPU_T_MIN && t1 < GPU_T_MAX && t1 < val)
		val = t1;
	if (val >= GPU_T_MAX || val >= ray->closest_t)
		return false;

	/* Height check */
	d_vec inter = point_at_t(*ray, val);
	double x = sqrt(vec_length_sq(vec_sub(inter, obj_orig)) - obj->radius * obj->radius);
	if (x > obj->hei_fov / 2.0)
		return false;

	ray->closest_idx = idx;
	ray->closest_t = val;
	/* Normal calculation */
	d_vec s0 = vec_sub(vec_sub(inter, obj_orig), vec_scale(obj_vec, x));
	d_vec s1 = vec_sub(vec_sub(inter, obj_orig), vec_scale(obj_vec, -x));
	if (vec_length(s0) < vec_length(s1))
		ray->normal = vec_normalize(s0);
	else
		ray->normal = vec_normalize(s1);
	return true;
}

__device__ bool gpu_hit_circle(d_ray *ray, t_gpu_obj *obj, int idx)
{
	d_vec obj_n = vec_from_arr(obj->vector);
	d_vec obj_o = vec_from_arr(obj->origin);
	double ortho = vec_dot(obj_n, ray->direction);

	if (ortho == 0.0)
		return false;
	double pln_d = vec_dot(obj_o, obj_n);
	double dis = vec_dot(obj_n, ray->origin);
	double t = (pln_d - dis) / ortho;
	if (t < GPU_T_MIN || t > GPU_T_MAX || t >= ray->closest_t)
		return false;
	d_vec hit_pt = point_at_t(*ray, t);
	double dist = vec_length(vec_sub(hit_pt, obj_o));
	if (dist > obj->radius)
		return false;
	ray->closest_idx = idx;
	ray->closest_t = t;
	ray->normal = obj_n;
	return true;
}

__device__ bool gpu_hit_square(d_ray *ray, t_gpu_obj *obj, int idx)
{
	d_vec obj_n = vec_from_arr(obj->vector);
	d_vec obj_o = vec_from_arr(obj->origin);
	double ortho = vec_dot(obj_n, ray->direction);

	if (ortho == 0.0)
		return false;
	double pln_d = vec_dot(obj_o, obj_n);
	double dis = vec_dot(obj_n, ray->origin);
	double t = (pln_d - dis) / ortho;
	if (t < GPU_T_MIN || t > GPU_T_MAX || t >= ray->closest_t)
		return false;
	d_vec hit_pt = point_at_t(*ray, t);
	d_vec diff = vec_sub(hit_pt, obj_o);
	/* Use vector2 as the "up" direction of the square */
	d_vec v2 = vec_from_arr(obj->vector2);
	d_vec side = vec_cross(obj_n, v2);
	double proj_u = fabs(vec_dot(diff, vec_normalize(side)));
	double proj_v = fabs(vec_dot(diff, vec_normalize(v2)));
	if (proj_u > obj->width / 2.0 || proj_v > obj->hei_fov / 2.0)
		return false;
	ray->closest_idx = idx;
	ray->closest_t = t;
	ray->normal = obj_n;
	return true;
}

/* ---- Hit any object ---- */

__device__ bool gpu_hit_object(d_ray *ray, t_gpu_obj *objs, int num_objs)
{
	bool hit = false;
	for (int i = 0; i < num_objs; i++)
	{
		if (objs[i].type == GPU_SPHERE && gpu_hit_sphere(ray, &objs[i], i))
			hit = true;
		else if (objs[i].type == GPU_LIGHT && gpu_hit_sphere(ray, &objs[i], i))
			hit = true;
		else if (objs[i].type == GPU_PLN && gpu_hit_plane(ray, &objs[i], i))
			hit = true;
		else if (objs[i].type == GPU_CYL && gpu_hit_cylinder(ray, &objs[i], i))
			hit = true;
		else if (objs[i].type == GPU_CIRCLE && gpu_hit_circle(ray, &objs[i], i))
			hit = true;
		else if (objs[i].type == GPU_SQUA && gpu_hit_square(ray, &objs[i], i))
			hit = true;
	}
	return hit;
}

/* ---- Color helpers ---- */

__device__ inline d_vec color_clamp_gpu(d_vec c)
{
	if (c.x > 1.0) c.x = 1.0; else if (c.x < 0.0) c.x = 0.0;
	if (c.y > 1.0) c.y = 1.0; else if (c.y < 0.0) c.y = 0.0;
	if (c.z > 1.0) c.z = 1.0; else if (c.z < 0.0) c.z = 0.0;
	return c;
}

__device__ d_vec gradient_gpu(d_ray *ray)
{
	double t = 0.5 * (ray->direction.y + 1.0);
	d_vec top = vec_scale(make_vec(0.1, 0.4, 1.0), 1.0 - t);
	d_vec bot = vec_scale(make_vec(1.0, 1.0, 1.0), t);
	return vec_add(top, bot);
}

/* ---- Find first light ---- */

__device__ int find_first_light(t_gpu_obj *objs, int num_objs)
{
	for (int i = 0; i < num_objs; i++)
		if (objs[i].type == GPU_LIGHT)
			return i;
	return -1;
}

/* ---- Soft shadow ray color (iterative with depth) ---- */

__device__ d_vec gpu_ray_color_soft(d_ray ray, t_gpu_obj *objs, int num_objs,
	t_gpu_config *cfg, int *seed)
{
	d_vec	color = make_vec(0, 0, 0);
	d_vec	attenuation = make_vec(1, 1, 1);
	int		depth = cfg->max_depth;

	for (int d = 0; d < depth; d++)
	{
		ray.closest_t = GPU_T_MAX;
		ray.closest_idx = -1;
		if (!gpu_hit_object(&ray, objs, num_objs))
		{
			if (cfg->sky)
				color = vec_add(color, vec_mul(attenuation, gradient_gpu(&ray)));
			break;
		}
		t_gpu_obj *hit_obj = &objs[ray.closest_idx];
		if (hit_obj->type == GPU_LIGHT)
		{
			d_vec light_col = vec_scale(vec_from_arr(hit_obj->color),
				hit_obj->width * cfg->light_factor);
			color = vec_add(color, vec_mul(attenuation, light_col));
			break;
		}
		/* Bounce - Lambertian diffuse */
		d_vec hit_point = point_at_t(ray, ray.closest_t);
		d_vec normal = ray.normal;
		if (!front_facing_gpu(ray.direction, normal))
			normal = vec_scale(normal, -1.0);
		/* Average multiple bounce directions */
		d_vec bounce_sum = make_vec(0, 0, 0);
		for (int b = 0; b < cfg->bounces; b++)
		{
			d_vec hemi = gpu_random_in_hemisphere(seed, normal);
			d_vec target = vec_add(hit_point, hemi);
			(void)target;
			/* Accumulate direction for averaging later - simplified:
			   just use last direction for the main ray */
			bounce_sum = vec_add(bounce_sum, hemi);
		}
		d_vec new_dir = vec_normalize(vec_div(bounce_sum, (double)cfg->bounces));
		/* Update attenuation with object color */
		d_vec obj_color = vec_from_arr(hit_obj->color);
		attenuation = vec_mul(attenuation, vec_scale(obj_color, cfg->albedo));
		/* Setup next ray */
		ray.origin = hit_point;
		ray.direction = new_dir;
	}
	return color;
}

/* ---- Hard shadow ray color (iterative) ---- */

__device__ d_vec gpu_ray_color_hard(d_ray ray, t_gpu_obj *objs, int num_objs,
	t_gpu_config *cfg)
{
	int light_idx = find_first_light(objs, num_objs);
	if (light_idx < 0)
		return make_vec(0, 0, 0);

	ray.closest_t = GPU_T_MAX;
	ray.closest_idx = -1;
	if (!gpu_hit_object(&ray, objs, num_objs))
	{
		if (cfg->sky)
			return gradient_gpu(&ray);
		return make_vec(0, 0, 0);
	}
	t_gpu_obj *hit_obj = &objs[ray.closest_idx];
	if (hit_obj->type == GPU_LIGHT)
		return vec_scale(vec_from_arr(hit_obj->color), hit_obj->width);

	/* Shadow ray to light */
	d_vec hit_point = point_at_t(ray, ray.closest_t);
	d_vec light_pos = vec_from_arr(objs[light_idx].origin);
	d_vec to_light = vec_normalize(vec_sub(light_pos, hit_point));

	/* Check if facing away from light */
	if (front_facing_gpu(ray.direction, ray.normal)
		== front_facing_gpu(to_light, ray.normal))
		return make_vec(0, 0, 0);

	/* Shadow test */
	d_ray shadow_ray;
	shadow_ray.origin = hit_point;
	shadow_ray.direction = to_light;
	shadow_ray.closest_t = GPU_T_MAX;
	shadow_ray.closest_idx = -1;

	if (!gpu_hit_object(&shadow_ray, objs, num_objs))
		return make_vec(0, 0, 0);
	if (objs[shadow_ray.closest_idx].type != GPU_LIGHT)
		return make_vec(0, 0, 0);

	/* Lambert shading */
	d_vec light_color = vec_scale(vec_from_arr(objs[light_idx].color),
		objs[light_idx].width);
	d_vec obj_color = vec_from_arr(hit_obj->color);
	d_vec att = vec_scale(obj_color, cfg->albedo);
	d_vec result = vec_mul(att, light_color);
	result = color_clamp_gpu(result);
	double factor = sin(vec_dot(ray.normal, to_light));
	result = vec_scale(result, factor);
	result = vec_abs(result);
	return result;
}

/* ---- Main render kernel ---- */

extern "C"
__global__ void render_kernel(t_gpu_obj *objs, int num_objs,
	t_gpu_cam *cam, t_gpu_config *cfg, double *accum, double *pixels,
	int sample_count, unsigned int base_seed)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x >= cfg->width || y >= cfg->height)
		return;

	int pixel_idx = (y * cfg->width + x) * 3;

	/* Per-thread random seed */
	int seed = (int)(base_seed ^ (x * 1973 + y * 9277 + sample_count * 26699));
	seed = gpu_xorshift(seed);

	/* Construct ray */
	d_ray ray;
	ray.origin = vec_from_arr(cam->origin);

	double col_f, row_f;
	if (cfg->soft_shadow)
	{
		/* Jitter for anti-aliasing */
		seed = gpu_xorshift(seed);
		col_f = (double)x + gpu_random_double(seed);
		seed = gpu_xorshift(seed);
		row_f = (double)y + gpu_random_double(seed);
	}
	else
	{
		col_f = (double)x;
		row_f = (double)y;
	}

	d_vec horiz = vec_from_arr(cam->horizontal);
	d_vec vert = vec_from_arr(cam->vertical);
	d_vec corner = vec_from_arr(cam->upper_left_corner);

	ray.direction = vec_add(vec_scale(horiz, col_f), vec_scale(vert, row_f));
	ray.direction = vec_add(corner, ray.direction);
	ray.direction = vec_normalize(ray.direction);
	ray.closest_t = GPU_T_MAX;
	ray.closest_idx = -1;

	/* Trace */
	d_vec color;
	if (cfg->soft_shadow)
		color = gpu_ray_color_soft(ray, objs, num_objs, cfg, &seed);
	else
		color = gpu_ray_color_hard(ray, objs, num_objs, cfg);

	/* Progressive accumulation */
	if (sample_count == 0)
	{
		accum[pixel_idx + 0] = color.x;
		accum[pixel_idx + 1] = color.y;
		accum[pixel_idx + 2] = color.z;
	}
	else
	{
		accum[pixel_idx + 0] = (accum[pixel_idx + 0] * sample_count + color.x)
			/ (sample_count + 1);
		accum[pixel_idx + 1] = (accum[pixel_idx + 1] * sample_count + color.y)
			/ (sample_count + 1);
		accum[pixel_idx + 2] = (accum[pixel_idx + 2] * sample_count + color.z)
			/ (sample_count + 1);
	}

	/* Add ambient and store final pixel */
	d_vec ambient = vec_from_arr(cfg->ambient);
	pixels[pixel_idx + 0] = accum[pixel_idx + 0] + ambient.x;
	pixels[pixel_idx + 1] = accum[pixel_idx + 1] + ambient.y;
	pixels[pixel_idx + 2] = accum[pixel_idx + 2] + ambient.z;
}
