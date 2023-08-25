# miniRT
miniRT is a 42's project that introduce us to the concept of Raytracing using C and a simple graphic library.

<p align="center">
  <img src="/scene_atoms.png" width="49%" />
  <img src="/scene_pillars.png" width="49%" />
</p>


## Description

We used codam's [MLX42](https://github.com/codam-coding-college/MLX42#download-and-build---mlx42) rather then the library provided in the project as it is more efficient and stable between hardwares.

## Installation

[GLFW](https://www.glfw.org/) necessary to use MLX42:
Install on .brew: https://formulae.brew.sh/formula/glfw (may need to update glfw path on Makefile)

```bash
git clone git@github.com:KayzaFlo/42_miniRT.git
make
```

## Features

##### Parsing
- Read and process any .rt valid file
- Draw the map associated in perspective view
- ESC or close window exit the program properly
- Handle Sphere, Plane and Cylinder primitives
- Handle One Ambient Lighting
- Handle One Point Light
- Handle One Camera
##### Rendering
- Use Raytracing
- Use Phong Reflexion Model (Ambient, Diffuse and Specular)
- Cast Hard Shadows
##### Interactions
- Can select any element by clicking on it or the text
- Handle Translation, Rotation and parameters change

## Usage

```
    ./miniRT [.rt file]
```
[ESC][Q] - Exit<br>
[Left Click] : Select element (Translation Mode)<br>
[Right Click] : Select element (Rotation Mode)<br>
[WASD][Ctrl][Space] : Control the Translation and Rotation once selected<br>
[Arrows] : Control primitives parameters when available (Sphere's & Cylinder's Radius, Cylinder's lenght)<br>

## License

[MIT](https://choosealicense.com/licenses/mit/)
