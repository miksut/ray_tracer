# Ray Tracer

This repository hosts an implementation of an offline high-quality renderer for 3D scenes based on ray tracing. This project is linked to a lecture offered by the [Visualization and MultiMedia Lab](https://www.ifi.uzh.ch/en/vmml/teaching.html) in the Department of Informatics at the University of Zurich, Switzerland.

---
## Project Description

This project implements an offline renderer to produce high-quality renderings of simple 3D scenes using ray tracing. The application builds upon a framework provided by the Visualization and MultiMedia Lab. 

The program starts in the _GLEmbreeTracer_ class which loads a scene composed of a set of drawables (i.e., lights, materials, and geometric objects) via a parser in the `loadScene` method. The input scene can be interactively navigated. Concretely, the viewpoint from which the ray-traced scene rendering is generated can be selected by freeely moving the camera in the scene. The viewpoint allows to define the viewing parameters for the raytracing process. Pressing a GUI button then performs the actual raytracing of the loaded scene. The raytracing itself is based on a wrapper class for the [Embree](https://www.embree.org/) library, which provides a high-level interface to the fundamental raytracing operations (e.g., creation of a spatial acceleration structure for scene objects, creation of rays, or the computation of ray-scene intersections).

This project implements the following functionality:

- **Ray Casting**: implementation of a rendering strategy that casts primary rays into the scene by using the camera and viewport parameters to define the origin and the direction of the rays. At every intersection between a primary ray and a scene object, shading computations are performed based on properties of the lights in the scene and the material of the hit surface. In addition to primary rays, shadow rays and secondary rays are casted at every intersection between the primary rays and the scene objects. This allows to take hard shadows and perfectly specular reflections into account. The maximum recursion depth for the secondary rays is customizable via the GUI. For the shading computations, a local illumination model as well as a _Whitted-style_ illumination model can be applied.

- **Anti-Aliasing Scheme**: the aliasing effect is addressed by implementing an anti-aliasing scheme for the raytracing algorithms. This scheme is based on the idea of casting multiple primary rays per pixel in combination with a sampling strategy. 

- **Soft Shadows**: including planar area lights into the scene is the starting point for implementing soft shadows. The surface of these area lights is sampled using a set of shadow rays via a light version of importance sampling. 

- **Multithreading**: the basic idea is to use multiple threads to process an image. This reduces the rendering time and increases the usability of the application. Specifically, each thread works on a dedicated part of the image. These parts are finally combined using the `runTracer` method. The composed image is then saved to disk (available formats: png and ppm).

Some exemplary image outputs are shown below.


<img
    src="/imgs/01_gd_view1.png"
    height="200"
    align="left">
    
    <img
    src="/imgs/01_gd_view2.png"
    height="200">
    

---

## Installation and Setup
This program has the following dependencies:

 1. OpenGL
 2. GLEW
 3. GLFW
 4. FreeImage
 5. Assimp

### Dependencies
OpenGL should already exist on the platform. The Assimp source code is included in this repository and will be built the first time when building this project.

**on Mac:**

Install the remaining three dependencies using homebrew:
```
brew install glew
brew install glfw3
brew install freeimage
```

**on Windows:**

Most of the dependencies are included in this repository. When running Cmake, choose "Visual Studio xx WIN64" or choose "Visual Studio xx" as the target platform. In the second case, make sure to definitely choose x64 in the next field.

Install embree using the windows installer (.msi) from the official website. Add %EMBREE_ROOT%/bin (replace %EMBREE_ROOT% with the folder where embree is installed) to the path environment variable. When running CMake, if embree is not found, fill embree_DIR with the address to the folder where embree is installed and run CMake again.

**on Linux:**

Install the remaining three dependencies using apt-get:
```
sudo apt-get install libglew-dev
sudo apt-get install libglfw3-dev
sudo apt-get install libfreeimage3 libfreeimage-dev
```

### Build
After installing the dependencies, use cmake to build the project. Make sure that the build folder is inside the project folder:

```
[project root]
	|-- build
	|-- CMake
	|-- doc
	|-- external
	|-- res
	|-- shader
	|-- src
	
```
In case of encountering an error when compiling kdtree_index.h in the FLANN library, add the following line:
```
#include <cmath>
```
In case of encountering an error when compiling serialization.h in the FLANN library, add the following lines (around line 92 where there are similar codes):
```
#ifdef _MSC_VER
BASIC_TYPE_SERIALIZER(unsigned __int64);
#endif
```
---
