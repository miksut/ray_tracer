Computer Graphics Lab

Suter Mike 13-110-671
Faruk Acibal 14-933-642

We compiled and worked on Windows as well as OSX. We did not try Linux.
The project also includes the git folder. We worked with GitHub as well, if you're interested in being invited to the private repo, please tell us.

------------------------General Code Overview-------------------------

The program starts in the GLEmbreeTracer class which has a Scene field object which is read by its parser in the loadScene method.
This scene has a list of drawables which are created by reading the scene file. Even the lights are drawables (except for directional lights, which are a simple struct).

During real time rendering, this list of drawables is used to render the scene in real time.

When executing a retracer we use one method per tracing algorithm. This method makes a pointer to the Base class "RayTracer" which it then executes by giving it to the runTracer() method.

Each RayTracer has a method to return a future float*, which represents the image. This method takes the camera, the samples for Antialiasing and the start and endpoints of the Y coordinate of the image (to allow for multiple threads to work on the same image).

Each thread works on a part of the image and the images are then combined in the runTracer() method, which then finally saves the image to disk.

We added a shadeLocal() and shadeWhitted() method to the Scene class. This is to make them usable in future RayTracers. These two methods are the main shading methods.

The area lights have a light version of importance sampling. We added three ranges of sampling stages (Low, Medium and High). Which, instead of sampling random points, sample important points on the respective surface. These points can be checked in their respective classes (e.g DrawableCircularAreaLight.cpp).


--------------------------Scene Changes--------------------------------

Meshes can now also have a position and a scale. They are simply listed after their filename in a new line.

Example Mesh:

O 1 #object with id 1
10  #has material id 10
M bunny.ply  #read file PLY/bunny.ply representing a mesh
-2.5 -10.8 3.0 20.0 #x y z position of mesh and scaling (20)


We added a room object to be read from the scene file. Each wall has its own material.

Example Room:

O 2	# Note: Object number 2-6 are reserved for room, continue with object number 7 after this
12	# material-id for 1st wall 
R 10.0 0.0 0.0 0.0 0.25 0.58 0.80  # simple room object (-> R) scaled by factor s and centered on [x,y,z] with vertex colors for walls (this does not affect viewport)
13 14 15 16 #material ids for the other walls

-------------------------GUI / USABILITY-------------------------------

- We added a sound / notification when raytracing is finished (toggable in GUI).
- We added Multithreading, because we think it makes a big difference in rendering times / usability.
- You can reload the scene during runtime to easily change the scene. It takes the name of a scene file in the scenes folder.
- You can output in two image formats: png and ppm.
- You can enter a filename for the exported image.

------------------------------------------------------------------------

We also included 3 sample scenes in res/scenes and some renders. We will have more renders for the final presentation then!