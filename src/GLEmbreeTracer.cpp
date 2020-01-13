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
      
    
    connectVar("lightDiffuse", &light.diffuseTerm.x);
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


    // create box for light position
    this->lightbox = std::make_shared<Cube>();
    if (!this->lightbox->createVertexArray(0, 1, 2, 3, 4 )) {
      return false;
    };
    this->lightbox->setPosition(glm::vec3(0.0, 0.5, -1.0));
    this->lightbox->setScaling(glm::vec3(0.05, 0.05, 0.05));
    this->lightbox->setMaterial(std::make_shared<Material>());

    // Init models
    this->sphere = std::make_shared<Sphere>(glm::vec4(2.f, 2.f, -1.f, .5f));
    if(!this->sphere->createVertexArray(0, 1, 2, 3, 4))
      return false;
    this->sphere->getMaterial()->ka = glm::vec3(0.4);


    this->cube = std::make_shared<Cube>();
    bool constructed = this->cube->createVertexArray(0, 1, 2, 3, 4);
    if (!constructed) return constructed;
    this->cube->setPosition(glm::vec3(-2.5, 0.5, 1.5));
    this->cube->setScaling(glm::vec3(1.5, 1.5, 1.5));
    this->cube->getMaterial()->ka = glm::vec3(0.4);


    programForMeshPhong = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Mesh_phong");
    programForMeshCook = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Mesh_cook");
    programForMeshBlinn = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Mesh_blinn");

    light.ambientTerm = glm::vec3(1.0, 1.0, 1.0);
    light.diffuseTerm = glm::vec3(1.0, 1.0, 1.0);
    light.specularTerm = glm::vec3(1.0, 1.0, 1.0);

    this->cubeNormaltex = std::make_shared<Texture>();
    this->cubeNormaltex->loadFromFile(this->getPathToExecutable() + "../../res/container_normal.jpg");
    this->cube->getMaterial()->normalTexture = cubeNormaltex;

    this->cubetex = std::make_shared<Texture>();
    this->cubetex->loadFromFile(this->getPathToExecutable() + "../../res/container.png");
    this->cube->getMaterial()->diffuseTexture=cubetex;
    this->cubetexSpec = std::make_shared<Texture>();
    this->cubetexSpec->loadFromFile(this->getPathToExecutable() + "../../res/container_specular.png");
    this->cube->getMaterial()->specTexture = cubetexSpec;

      
    _parser = std::make_shared<parser>(this, this->getPathToExecutable() + "sample_scene.cgl");
    _scene = _parser->getScene();
    _scene->InitializeViewPort(this);
    return constructed;
  }

  bool GLEmbreeTracer::update(double dt)
  {
    updateGui();

	//reset file name if not set
	if (tracedFileName[0] == '\0') {
		std::string defaultName = "tracedImage";
		strcpy(tracedFileName, defaultName.c_str());
	}

    this->addLightVariables(programForMeshPhong);
    this->addLightVariables(programForMeshCook);
    this->addLightVariables(programForMeshBlinn);

    lightbox->getMaterial()->hasObjectColor=false;
    lightbox->getMaterial()->color = light.diffuseTerm;
    lightbox->getMaterial()->illumination = 1;
    lightbox->getMaterial()->kd = glm::vec3(0);
    lightbox->getMaterial()->ka = glm::vec3(0);

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
      case 2:
        activeProgram = programForMeshCook;
        break;
    }

    lightbox->draw(this->cam.getProjectionMatrix(),this->cam.getViewMatrix(),activeProgram);
    this->sphere->draw(this->cam.getProjectionMatrix(),this->cam.getViewMatrix(),activeProgram);
    this->cube->draw(this->cam.getProjectionMatrix(),this->cam.getViewMatrix(),activeProgram);

    renderGui();
    return true;
  }

  void GLEmbreeTracer::addLightVariables(const std::shared_ptr<ShaderProgram>& _program) {
    _program->setUniform3fv("camPos", this->cam.getPosition());
    _program->setUniform3fv("light.position", this->lightbox->getPosition());
    _program->setUniform3fv("light.ambient", light.ambientTerm);
    _program->setUniform3fv("light.diffuse", light.diffuseTerm);
    _program->setUniform3fv("light.specular",light.specularTerm);
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
      
      ImageSaver::saveImageAsPPM(tracedFileName, getWindowSize().x, getWindowSize().y, image);
      
      delete[] image;
  }
}

