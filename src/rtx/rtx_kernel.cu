/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtx_kernel.cu                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbetz <rbetz@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:00:00 by rbetz             #+#    #+#             */
/*   Updated: 2026/05/22 10:00:00 by rbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtx.h"
#include <float.h>

#define GPU_T_MIN 0.001f
#define GPU_T_MAX 1.0e30f

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

/* ---- Vector math (device inline, float) ---- */

struct f_vec { float x, y, z; };

__device__ inline f_vec make_vec(float x, float y, float z)
{
	f_vec v;
	v.x = x; v.y = y; v.z = z;
	return v;
}

__device__ inline f_vec vec_add(f_vec a, f_vec b)
{
	return make_vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

__device__ inline f_vec vec_sub(f_vec a, f_vec b)
{
	return make_vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

__device__ inline f_vec vec_mul(f_vec a, f_vec b)
{
	return make_vec(a.x * b.x, a.y * b.y, a.z * b.z);
}

__device__ inline f_vec vec_scale(f_vec v, float s)
{
	return make_vec(v.x * s, v.y * s, v.z * s);
}

__device__ inline f_vec vec_div(f_vec v, float s)
{
	return make_vec(v.x / s, v.y / s, v.z / s);
}

__device__ inline float vec_dot(f_vec a, f_vec b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

__device__ inline f_vec vec_cross(f_vec a, f_vec b)
{
	return make_vec(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

__device__ inline float vec_length_sq(f_vec v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

__device__ inline float vec_length(f_vec v)
{
	return sqrtf(vec_length_sq(v));
}

__device__ inline f_vec vec_normalize(f_vec v)
{
	float len_sq = vec_length_sq(v);
	if (len_sq == 0.0f)
		return v;
	float inv_len = rsqrtf(len_sq);
	return make_vec(v.x * inv_len, v.y * inv_len, v.z * inv_len);
}

__device__ inline f_vec vec_abs(f_vec v)
{
	return make_vec(fabsf(v.x), fabsf(v.y), fabsf(v.z));
}

__device__ inline f_vec vec_from_arr(const float *a)
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

__device__ inline float gpu_random_float(int seed)
{
	float r = (float)seed / (float)(2147483647.0f + 1.0f);
	if (r < 0.0f)
		r = -r;
	return r;
}

__device__ f_vec gpu_random_vector(int seed)
{
	float x, y, z;
	seed = gpu_xorshift(seed);
	x = gpu_random_float(seed);
	seed = gpu_xorshift(seed);
	y = gpu_random_float(seed);
	seed = gpu_xorshift(seed);
	z = gpu_random_float(seed);
	return make_vec(x * 2.0f - 1.0f, y * 2.0f - 1.0f, z * 2.0f - 1.0f);
}

__device__ f_vec gpu_random_in_hemisphere(int *seed, f_vec normal)
{
	/* Cosine-weighted hemisphere sampling - no rejection loop, no divergence */
	*seed = gpu_xorshift(*seed);
	float u1 = gpu_random_float(*seed);
	*seed = gpu_xorshift(*seed);
	float u2 = gpu_random_float(*seed);

	/* Build orthonormal basis around normal */
	f_vec w = normal;
	f_vec a;
	if (fabsf(w.x) > 0.9f)
		a = make_vec(0.0f, 1.0f, 0.0f);
	else
		a = make_vec(1.0f, 0.0f, 0.0f);
	f_vec u = vec_normalize(vec_cross(a, w));
	f_vec v = vec_cross(w, u);

	/* Sample cosine-weighted direction */
	float phi = 2.0f * 3.14159265f * u1;
	float sin_theta = sqrtf(u2);
	float cos_theta = sqrtf(1.0f - u2);

	f_vec dir;
	dir.x = u.x * cosf(phi) * sin_theta + v.x * sinf(phi) * sin_theta + w.x * cos_theta;
	dir.y = u.y * cosf(phi) * sin_theta + v.y * sinf(phi) * sin_theta + w.y * cos_theta;
	dir.z = u.z * cosf(phi) * sin_theta + v.z * sinf(phi) * sin_theta + w.z * cos_theta;
	return vec_normalize(dir);
}

/* ---- Ray structure ---- */

struct f_ray
{
	f_vec	origin;
	f_vec	direction;
	float	closest_t;
	int		closest_idx;
	f_vec	normal;
};

/* ---- Point at t ---- */

__device__ inline f_vec point_at_t(f_ray ray, float t)
{
	return vec_add(ray.origin, vec_scale(ray.direction, t));
}

__device__ inline bool front_facing_gpu(f_vec ray_dir, f_vec face_normal)
{
	return vec_dot(ray_dir, face_normal) < 0.0f;
}

/* ---- Intersection tests ---- */

__device__ bool gpu_hit_sphere(f_ray *ray, t_gpu_obj *obj, int idx)
{
	f_vec	oc = vec_sub(ray->origin, vec_from_arr(obj->origin));
	/* ray->direction is normalized, so a = 1.0 */
	float	a = vec_length_sq(ray->direction);
	float	b = vec_dot(oc, ray->direction);
	float	oc_len_sq = vec_length_sq(oc);
	float	disc = b * b - (a * oc_len_sq - obj->radius * obj->radius);

	if (disc <= 0.0f)
		return false;
	disc = sqrtf(disc);
	float t = (-b - disc) / a;
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
	f_vec hit_pt = point_at_t(*ray, t);
	ray->normal = vec_div(vec_sub(hit_pt, vec_from_arr(obj->origin)), obj->radius);
	return true;
}

__device__ bool gpu_hit_plane(f_ray *ray, t_gpu_obj *obj, int idx)
{
	f_vec obj_n = vec_from_arr(obj->vector);
	f_vec obj_o = vec_from_arr(obj->origin);
	float ortho = vec_dot(obj_n, ray->direction);

	if (ortho == 0.0f)
		return false;
	float pln_d = vec_dot(obj_o, obj_n);
	float dis = vec_dot(obj_n, ray->origin);
	float t = (pln_d - dis) / ortho;
	if (t < GPU_T_MIN || t > GPU_T_MAX)
		return false;
	if (t >= ray->closest_t)
		return false;
	ray->closest_idx = idx;
	ray->closest_t = t;
	ray->normal = obj_n;
	return true;
}

__device__ bool gpu_hit_cylinder(f_ray *ray, t_gpu_obj *obj, int idx)
{
	f_vec obj_vec = vec_from_arr(obj->vector);
	f_vec obj_orig = vec_from_arr(obj->origin);
	f_vec d = vec_cross(ray->direction, obj_vec);
	f_vec cros = vec_cross(vec_sub(ray->origin, obj_orig), obj_vec);

	float a0 = vec_length_sq(d);
	float a1 = 2.0f * vec_dot(d, cros);
	float a2 = vec_length_sq(cros) - (obj->radius * obj->radius);

	if (a0 == 0.0f)
		return false;
	float disc = a1 * a1 - 4.0f * a0 * a2;
	if (disc < 0.0f)
		return false;
	disc = sqrtf(disc);
	float t0 = (-a1 - disc) / (2.0f * a0);
	float t1 = (-a1 + disc) / (2.0f * a0);

	/* Pick smallest valid t */
	float val = GPU_T_MAX;
	if (t0 > GPU_T_MIN && t0 < GPU_T_MAX)
		val = t0;
	if (t1 > GPU_T_MIN && t1 < GPU_T_MAX && t1 < val)
		val = t1;
	if (val >= GPU_T_MAX || val >= ray->closest_t)
		return false;

	/* Height check (compare squared to avoid sqrtf) */
	f_vec inter = point_at_t(*ray, val);
	float dist_sq = vec_length_sq(vec_sub(inter, obj_orig));
	float x_sq = dist_sq - obj->radius * obj->radius;
	float half_h = obj->hei_fov / 2.0f;
	if (x_sq > half_h * half_h)
		return false;
	float x = sqrtf(x_sq);

	ray->closest_idx = idx;
	ray->closest_t = val;
	/* Normal calculation */
	f_vec s0 = vec_sub(vec_sub(inter, obj_orig), vec_scale(obj_vec, x));
	f_vec s1 = vec_sub(vec_sub(inter, obj_orig), vec_scale(obj_vec, -x));
	if (vec_length(s0) < vec_length(s1))
		ray->normal = vec_normalize(s0);
	else
		ray->normal = vec_normalize(s1);
	return true;
}

__device__ bool gpu_hit_circle(f_ray *ray, t_gpu_obj *obj, int idx)
{
	f_vec obj_n = vec_from_arr(obj->vector);
	f_vec obj_o = vec_from_arr(obj->origin);
	float ortho = vec_dot(obj_n, ray->direction);

	if (ortho == 0.0f)
		return false;
	float pln_d = vec_dot(obj_o, obj_n);
	float dis = vec_dot(obj_n, ray->origin);
	float t = (pln_d - dis) / ortho;
	if (t < GPU_T_MIN || t > GPU_T_MAX || t >= ray->closest_t)
		return false;
	f_vec hit_pt = point_at_t(*ray, t);
	float dist = vec_length(vec_sub(hit_pt, obj_o));
	if (dist > obj->radius)
		return false;
	ray->closest_idx = idx;
	ray->closest_t = t;
	ray->normal = obj_n;
	return true;
}

__device__ bool gpu_hit_square(f_ray *ray, t_gpu_obj *obj, int idx)
{
	f_vec obj_n = vec_from_arr(obj->vector);
	f_vec obj_o = vec_from_arr(obj->origin);
	float ortho = vec_dot(obj_n, ray->direction);

	if (ortho == 0.0f)
		return false;
	float pln_d = vec_dot(obj_o, obj_n);
	float dis = vec_dot(obj_n, ray->origin);
	float t = (pln_d - dis) / ortho;
	if (t < GPU_T_MIN || t > GPU_T_MAX || t >= ray->closest_t)
		return false;
	f_vec hit_pt = point_at_t(*ray, t);
	f_vec diff = vec_sub(hit_pt, obj_o);
	/* Use vector2 as one axis of the square, cross for the other */
	f_vec v2 = vec_from_arr(obj->vector2);
	f_vec side = vec_cross(obj_n, v2);
	float proj_u = fabsf(vec_dot(diff, vec_normalize(side)));
	float proj_v = fabsf(vec_dot(diff, vec_normalize(v2)));
	if (proj_v > obj->radius / 2.0f || proj_u > obj->width / 2.0f)
		return false;
	ray->closest_idx = idx;
	ray->closest_t = t;
	ray->normal = obj_n;
	return true;
}

/* ---- Hit any object ---- */

__device__ bool gpu_hit_object(f_ray *ray, t_gpu_obj *objs, int num_objs)
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

__device__ inline f_vec color_clamp_gpu(f_vec c)
{
	if (c.x > 1.0f) c.x = 1.0f; else if (c.x < 0.0f) c.x = 0.0f;
	if (c.y > 1.0f) c.y = 1.0f; else if (c.y < 0.0f) c.y = 0.0f;
	if (c.z > 1.0f) c.z = 1.0f; else if (c.z < 0.0f) c.z = 0.0f;
	return c;
}

__device__ f_vec gradient_gpu(f_ray *ray)
{
	float t = 0.5f * (ray->direction.y + 1.0f);
	f_vec top = vec_scale(make_vec(0.1f, 0.4f, 1.0f), 1.0f - t);
	f_vec bot = vec_scale(make_vec(1.0f, 1.0f, 1.0f), t);
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

__device__ f_vec gpu_ray_color_soft(f_ray ray, t_gpu_obj *objs, int num_objs,
	t_gpu_config *cfg, int *seed)
{
	f_vec	color = make_vec(0.0f, 0.0f, 0.0f);
	f_vec	attenuation = make_vec(1.0f, 1.0f, 1.0f);
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
			f_vec light_col = vec_scale(vec_from_arr(hit_obj->color),
				hit_obj->width * cfg->light_factor);
			color = vec_add(color, vec_mul(attenuation, light_col));
			break;
		}
		/* Bounce - Lambertian diffuse */
		f_vec hit_point = point_at_t(ray, ray.closest_t);
		f_vec normal = ray.normal;
		if (!front_facing_gpu(ray.direction, normal))
			normal = vec_scale(normal, -1.0f);
		/* Single cosine-weighted bounce direction (no averaging loop) */
		f_vec new_dir = gpu_random_in_hemisphere(seed, normal);
		/* Update attenuation with object color */
		f_vec obj_color = vec_from_arr(hit_obj->color);
		attenuation = vec_mul(attenuation, vec_scale(obj_color, cfg->albedo));
		/* Setup next ray */
		ray.origin = hit_point;
		ray.direction = new_dir;
	}
	return color;
}

/* ---- Hard shadow ray color (iterative) ---- */

__device__ f_vec gpu_ray_color_hard(f_ray ray, t_gpu_obj *objs, int num_objs,
	t_gpu_config *cfg)
{
	int light_idx = find_first_light(objs, num_objs);
	if (light_idx < 0)
		return make_vec(0.0f, 0.0f, 0.0f);

	ray.closest_t = GPU_T_MAX;
	ray.closest_idx = -1;
	if (!gpu_hit_object(&ray, objs, num_objs))
	{
		if (cfg->sky)
			return gradient_gpu(&ray);
		return make_vec(0.0f, 0.0f, 0.0f);
	}
	t_gpu_obj *hit_obj = &objs[ray.closest_idx];
	if (hit_obj->type == GPU_LIGHT)
		return vec_scale(vec_from_arr(hit_obj->color), hit_obj->width);

	/* Shadow ray to light */
	f_vec hit_point = point_at_t(ray, ray.closest_t);
	f_vec light_pos = vec_from_arr(objs[light_idx].origin);
	f_vec to_light = vec_normalize(vec_sub(light_pos, hit_point));

	/* Check if facing away from light */
	if (front_facing_gpu(ray.direction, ray.normal)
		== front_facing_gpu(to_light, ray.normal))
		return make_vec(0.0f, 0.0f, 0.0f);

	/* Shadow test */
	f_ray shadow_ray;
	shadow_ray.origin = hit_point;
	shadow_ray.direction = to_light;
	shadow_ray.closest_t = GPU_T_MAX;
	shadow_ray.closest_idx = -1;

	if (!gpu_hit_object(&shadow_ray, objs, num_objs))
		return make_vec(0.0f, 0.0f, 0.0f);
	if (objs[shadow_ray.closest_idx].type != GPU_LIGHT)
		return make_vec(0.0f, 0.0f, 0.0f);

	/* Lambert shading */
	f_vec light_color = vec_scale(vec_from_arr(objs[light_idx].color),
		objs[light_idx].width);
	f_vec obj_color = vec_from_arr(hit_obj->color);
	f_vec att = vec_scale(obj_color, cfg->albedo);
	f_vec result = vec_mul(att, light_color);
	result = color_clamp_gpu(result);
	float factor = sinf(vec_dot(ray.normal, to_light));
	result = vec_scale(result, factor);
	result = vec_abs(result);
	return result;
}

/* ---- Main render kernel ---- */

extern "C"
__global__ void render_kernel(t_gpu_obj *objs, int num_objs,
	t_gpu_cam *cam, t_gpu_config *cfg, float *accum, float *pixels,
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
	f_ray ray;
	ray.origin = vec_from_arr(cam->origin);

	float col_f, row_f;
	if (cfg->soft_shadow)
	{
		/* Jitter for anti-aliasing */
		seed = gpu_xorshift(seed);
		col_f = (float)x + gpu_random_float(seed);
		seed = gpu_xorshift(seed);
		row_f = (float)y + gpu_random_float(seed);
	}
	else
	{
		col_f = (float)x;
		row_f = (float)y;
	}

	f_vec horiz = vec_from_arr(cam->horizontal);
	f_vec vert = vec_from_arr(cam->vertical);
	f_vec corner = vec_from_arr(cam->upper_left_corner);

	ray.direction = vec_add(vec_scale(horiz, col_f), vec_scale(vert, row_f));
	ray.direction = vec_add(corner, ray.direction);
	ray.direction = vec_normalize(ray.direction);
	ray.closest_t = GPU_T_MAX;
	ray.closest_idx = -1;

	/* Trace */
	f_vec color;
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
	f_vec ambient = vec_from_arr(cfg->ambient);
	pixels[pixel_idx + 0] = accum[pixel_idx + 0] + ambient.x;
	pixels[pixel_idx + 1] = accum[pixel_idx + 1] + ambient.y;
	pixels[pixel_idx + 2] = accum[pixel_idx + 2] + ambient.z;
}

/* ---- RGBA conversion kernel (gamma correct + pack to uint32) ---- */

extern "C"
__global__ void pixels_to_rgba_kernel(float *pixels, unsigned int *rgba,
	int num_pixels)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i >= num_pixels)
		return;

	const float gamma_val = 1.0f / 2.2f;
	float r = pixels[i * 3 + 0];
	float g = pixels[i * 3 + 1];
	float b = pixels[i * 3 + 2];

	/* Clamp */
	r = fminf(fmaxf(r, 0.0f), 1.0f);
	g = fminf(fmaxf(g, 0.0f), 1.0f);
	b = fminf(fmaxf(b, 0.0f), 1.0f);

	/* Gamma correction */
	r = powf(r, gamma_val);
	g = powf(g, gamma_val);
	b = powf(b, gamma_val);

	/* Pack for MLX42: expects [R,G,B,A] bytes in memory.
	   On little-endian x86: byte[0]=low bits, so R goes in bits 0-7 */
	unsigned int ri = (unsigned int)(r * 255.0f);
	unsigned int gi = (unsigned int)(g * 255.0f);
	unsigned int bi = (unsigned int)(b * 255.0f);
	rgba[i] = ri | (gi << 8) | (bi << 16) | (255u << 24);
}
