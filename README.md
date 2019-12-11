Computer Graphics Lab

This program has the following dependencies:

 1. OpenGL
 2. GLEW
 3. GLFW
 4. FreeImage
 5. Assimp

## Dependencies
OpenGL should already exist on your platform.
Assimp source code is included in this repository and will be built the first time you build this project.

**on Mac:**

You can install the remaining three dependencies using homebrew:
```
brew install glew
brew install glfw3
brew install freeimage
```

**on Windows:**

Most of the dependencies are included in this repository. When running Cmake, choose "Visual Studio xx WIN64" or choose "Visual Studio xx" as your target platform. In the second case, make sure to definitely choose x64 in the next field.

Install embree using the windows installer (.msi) from the official website. Add %EMBREE_ROOT%/bin (replace %EMBREE_ROOT% with the folder where you installed embree) to the path environment variable. When running CMake, if embree is not found, fill embree_DIR with the address to the folder where you installed embree and run CMake again.

**on Linux:**

You can install the remaining three dependencies using apt-get:
```
sudo apt-get install libglew-dev
sudo apt-get install libglfw3-dev
sudo apt-get install libfreeimage3 libfreeimage-dev
```

## Build
After installing the dependencies you should be able to use cmake to build the project. Make sure that the build folder is inside the project folder:

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
In case you encounter an error when compiling kdtree_index.h in the FLANN library, add the following line:
```
#include <cmath>
```
In case you encounter an error when compiling serialization.h in the FLANN library, add the following lines (around line 92 where there are similar codes):
```
#ifdef _MSC_VER
BASIC_TYPE_SERIALIZER(unsigned __int64);
#endif
```


## Run
When running the project, the output should look like [root]/doc/starting_scene.png (the Menu might be collapsed)
![Starting Scene](./doc/starting_scene.png)

## Note
Contact us if you have any problem building the project.
