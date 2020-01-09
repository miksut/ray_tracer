#ifndef Example2_Main_h
#define Example2_Main_h

#include "GLEmbreeTracer.h"

#include "parser.h"

#include <iostream>

int main(int argc, char *argv[])
{
  //	parser load_scene;
  //	load_scene("../../scene.cgl");
  //	return 0;

  if(argv[0] != nullptr) {
    // get path to executable from command line argument
    std::string exePath(argv[0]);

    // extract the folder where the executable is. For us usually /build/<configuration>
    exePath = exePath.substr(0, exePath.find_last_of("/\\")+1);

    // create the app:
    // - use GLExample for task 1 (multi-resolution point cloud viewer)
    cgCourse::GLEmbreeTracer app(glm::uvec2(1600, 900), std::string("OpenGL Example"), exePath);
    // - use GLEmbreeTracer for task 2 (ray tracing)
    //cgCourse::GLExample app(glm::uvec2(1600, 900), std::string("OpenGL Example"), exePath);

    // run the app
    app.run();

    // exit if the app is finished.
    exit(0);
  }
  // if there is a problem with the incoming arguments
  std::cout << "You might need to specify argv[0] somehow: " << argv[0] << std::endl;
}

#endif
