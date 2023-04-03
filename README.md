# 42 miniRT Project
This project is a small selfcoded Raytracer from [fkernbac](https://github.com/fkernbac) and [rbetz](https://github.com/Alphacharge).
It's using the [glfw Lib](https://github.com/glfw/glfw), [MLX42 V2.3.0](https://github.com/codam-coding-college/MLX42/commit/bf5dd7085b403974dd2d4e1e217877a518fc8915) and my [libft Lib](https://github.com/Alphacharge/mylibft/commit/37dc7a19c7b4b2734c7a4ccf9407ca715a660866).

All Dependencies are included or should get installed during the Make process.
## Installation
This project should compile under Mac OS and Unix:
```
git clone https://github.com/Alphacharge/miniRT.git
cd miniRT
make
```

## Describtion
It contains following Objects:
- Cameras
- Ambientlights
- Lights
- Planes
- Spheres
- Cylinders
- Rectangles

Additional you can declare a * *Resolution* * in the Scenefile.

This Raytracer is multithreaded, handles hard shadows as soft shadows [shadows](https://www.peachpit.com/articles/article.aspx?p=486505&seqNum=6) also.

You can declare all Objects multiple times, expect Resolution.
## Using
``./miniRT scenes/box.rt``

Keyhooks:
+ ESC	Exit Programm
+ Space	Switch to next Camera
+ W		Move up
+ S		Move down
+ A		Move left
+ D		Move right
+ E		Zoom in
+ Q		Zoom out

(Moving depence on absolut Axis)
## Pictures