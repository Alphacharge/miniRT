# 42 miniRT Project
This project is a selfcoded raytracer from [fkernbac](https://github.com/fkernbac) and [rbetz](https://github.com/Alphacharge).
It's using the [glfw Lib](https://github.com/glfw/glfw), [MLX42 V2.3.0](https://github.com/codam-coding-college/MLX42/commit/bf5dd7085b403974dd2d4e1e217877a518fc8915) and my [libft Lib](https://github.com/Alphacharge/mylibft/releases/tag/v1.0.0).

All dependencies are included or should get installed during the Make process.
## Installation
This project should compile under Mac OS and Unix:
```
git clone https://github.com/Alphacharge/miniRT.git
cd miniRT
make
```

## Description
It contains following objects:
- Cameras
- Ambientlights
- Lights
- Planes
- Spheres
- Cylinders
- Rectangles

Additionaly you can declare a * *Resolution* * in the scenefile.

This raytracer is multithreaded, handles hard shadows as soft [shadows](https://www.peachpit.com/articles/article.aspx?p=486505&seqNum=6) also.

You can declare all objects multiple times, expect resolution.
## Usage
``./miniRT scenes/box.rt``

Keyhooks:
+ ESC	Exit programm
+ Space	switch to next camera
+ W		Move up
+ S		Move down
+ A		Move left
+ D		Move right
+ E		Zoom in
+ Q		Zoom out

(Moving depence on absolut axis)
## Pictures
