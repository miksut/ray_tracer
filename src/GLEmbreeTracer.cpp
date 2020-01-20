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

#include "BaseTracer.h"

#include <thread>
#include <chrono>

namespace cgCourse
{
	GLEmbreeTracer::GLEmbreeTracer(glm::uvec2 _windowSize, std::string _title, std::string _exepath)
		: GLApp(_windowSize, _title, _exepath, false)
	{
		this->mvpMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		GLApp::current = this;
	}


	bool GLEmbreeTracer::init()
	{
		initGui(window_);

		connectVar("shadingAlgorithm", &shadingAlgorithm);
		connectVar("tracedFileName", &tracedFileName);
		connectVar("imageFormat", &imageFormat);
		connectVar("threads", &threads);
        connectVar("samplesAA", &samplesAA);

		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		this->cam.create(this->getFramebufferSize(), this->getWindowSize(),
			glm::vec3(0, 0, 26),
			glm::vec3(0, -0.5, 0),
			glm::vec3(0, 1, 0));
		InputManager::registerInputAcceptor(&cam);
		connectVar("cameraType", &cam.getType());


		programForMeshPhong = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Mesh_phong");
		programForMeshBlinn = std::make_shared<ShaderProgram>(this->getPathToExecutable() + "../../shader/Mesh_blinn");
        
        // load the default scene
        loadScene((char*)std::string("default.cgl").c_str());

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

		switch (shadingAlgorithm) {
		case 0:
			activeProgram = programForMeshPhong;
			break;
		case 1:
			activeProgram = programForMeshBlinn;
			break;
		}

		activeProgram->setUniform3fv("camPos", this->cam.getPosition());

        // render our own scene object
		this->_scene->draw(this->cam.getProjectionMatrix(), this->cam.getViewMatrix(), activeProgram);

		renderGui();
		return true;
	}


	bool GLEmbreeTracer::end()
	{
		return true;
	}

	void GLEmbreeTracer::loadScene(char* sceneName)
	{
        // Initialize parser and read scene into scene field
        std::string str(sceneName);
		_parser = std::make_shared<parser>(this, this->getPathToExecutable(), "../../res/scenes/" + str);
		_scene = _parser->getScene();

        // Since we use the scene for real time rendering, we need to set uniforms for all shaders
		_scene->addLightVariables(programForMeshBlinn);
		_scene->addLightVariables(programForMeshPhong);
	}

	void GLEmbreeTracer::rayCaster(bool antiAliasing)
	{
        //raycaster does not have recursiond and is not whitted (last parameter)
		auto tracer = new BaseTracer(getWindowSize().x, getWindowSize().y, _scene, 0, antiAliasing, false);
		runTracer(tracer);
	}

	void GLEmbreeTracer::whittedTracer(bool antiAliasing, int recursions)
	{
        //whitted tracer uses recursion (2nd last) and is whitted (last) parameter
		auto tracer = new BaseTracer(getWindowSize().x, getWindowSize().y, _scene, recursions, antiAliasing, true);
		runTracer(tracer);
	}

	void GLEmbreeTracer::runTracer(RayTracer* tracer) {
        //measure time for raytracing
		auto start = std::chrono::high_resolution_clock::now();
        
		std::cout << "Starting tracing with " << threads << " threads..." << std::endl;
		int y = getWindowSize().y;
		float heightPerThread = (y / (float)threads);   // calculate the height per thread

		std::vector<std::future<float*>> futures;       // futures for images to be traced
		std::vector<int> imageSizes;                    // image sizes of these images
        
        // start each thread and save its image size + their future
		for (int i = 0; i < threads; i++) {
			int start = (int)(i * heightPerThread);
			int end = (int)(i * heightPerThread + heightPerThread);
			imageSizes.push_back((end - start) * getWindowSize().x * 3);
			futures.push_back(tracer->start(cam, samplesAA, start, end));
		}
        
        // wait on threads to finish
		std::vector<float*> result;
		for (auto& e : futures) {
			result.push_back(e.get());
		}
        
        // construct image from pieces
		float* image = new float[getWindowSize().x * getWindowSize().y * 3];
		int loc = 0;
		for (int i = 0; i < result.size(); i++) {
			memcpy(image + loc, result[i], imageSizes[i] * sizeof(float));
			loc += imageSizes[i];
		}
        
        // save image to disk
		if (this->imageFormat == 0) {
			ImageSaver::saveImageAsPPM(this->getPathToExecutable() + "../../" + tracedFileName, getWindowSize().x, getWindowSize().y, image);
		}
		else {
			ImageSaver::saveImageAsPNG(this->getPathToExecutable() + "../../" + tracedFileName, getWindowSize().x, getWindowSize().y, image);
		};

		delete[] image;
        
        // stop timer and output timing + sound effect
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		std::cout << "Raytracing took " << duration.count() << " seconds..." << std::endl;
		std::cout << '\a';
	}
}

