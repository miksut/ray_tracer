#include "GLEmbreeTracer.h"

#include "Cube.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
#include "Gui.h"
#include <memory>

#include "SimpleRayTracer.h"


namespace cgCourse
{
  GLEmbreeTracer::GLEmbreeTracer(glm::uvec2 _windowSize, std::string _title, std::string _exepath)
    : GLApp(_windowSize, _title, _exepath, false)
  {
    this->mvpMatrix = glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    GLApp::current = this;
  }


  bool GLEmbreeTracer::init()
  {
    initGui(window_);
    
    connectVar("shadingAlgorithm", &shadingAlgorithm);
	connectVar("tracedFileName", &tracedFileName);
	connectVar("imageFormat", &imageFormat);

    // Framebuffer size and window size may be different in high-DPI displays
    // setup camera with standard view (static for our case)
    this->cam.create(this->getFramebufferSize(),this->getWindowSize(),
                     glm::vec3(5, 5, -5),
                     glm::vec3(0, 0, 0),
                     glm::vec3(0, 1, 0));
    InputManager::registerInputAcceptor(&cam);
    connectVar("cameraType", &cam.getType());


    programForMeshPhong = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Mesh_phong");
    programForMeshBlinn = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Mesh_blinn");

    _parser = std::make_shared<parser>(this, this->getPathToExecutable() + "../../res/scenes/pointlights_spheres.cgl");
    _scene = _parser->getScene();

	_scene->addLightVariables(programForMeshBlinn);
	_scene->addLightVariables(programForMeshPhong);

    return true;
  }

  bool GLEmbreeTracer::update(double dt)
  {
    updateGui();

	//reset file name if not set
	if (tracedFileName[0] == '\0') {
		std::string defaultName = "tracedImage";
		strcpy(tracedFileName, defaultName.c_str());
	}

    return true;
  }

  bool GLEmbreeTracer::render()
  {
    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    // Clear the color and depth buffers
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    bindDefaultFrameBuffer(getFramebufferSize());
    clearDefaultFrameBuffer();

    switch (shadingAlgorithm){
      case 0:
        activeProgram = programForMeshPhong;
        break;
      case 1:
        activeProgram = programForMeshBlinn;
        break;
    }

	activeProgram->setUniform3fv("camPos", this->cam.getPosition());

	this->_scene->draw(this->cam.getProjectionMatrix(), this->cam.getViewMatrix(), activeProgram);

    renderGui();
    return true;
  }


  bool GLEmbreeTracer::end()
  {
    return true;
  }

  void GLEmbreeTracer::tracer()
  {
      auto tracer = std::make_shared<SimpleRayTracer>(getWindowSize().x, getWindowSize().y, _scene);
      
      auto futureImage = tracer->start(cam, 1);
      futureImage.wait();
      auto image = futureImage.get();
      
      ImageSaver::saveImageAsPPM(this->getPathToExecutable() + "../../" + tracedFileName, getWindowSize().x, getWindowSize().y, image);
      
      delete[] image;
  }
}

