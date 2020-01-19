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
#include "RayCaster.h"
#include "WhittedTracer.h"

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

		_parser = std::make_shared<parser>(this, this->getPathToExecutable(), "../../res/scenes/default.cgl");
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

		switch (shadingAlgorithm) {
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

	void GLEmbreeTracer::loadScene(char* sceneName)
	{
		std::string str(sceneName);
		_parser = std::make_shared<parser>(this, this->getPathToExecutable(), "../../res/scenes/" + str);
		_scene = _parser->getScene();

		_scene->addLightVariables(programForMeshBlinn);
		_scene->addLightVariables(programForMeshPhong);
	}

	void GLEmbreeTracer::tracer()
	{
		auto tracer = std::unique_ptr<RayTracer>(new SimpleRayTracer(getWindowSize().x, getWindowSize().y, _scene));
		runTracer(tracer);
	}

	void GLEmbreeTracer::rayCaster()
	{
		auto tracer = std::unique_ptr<RayTracer>(new RayCaster(getWindowSize().x, getWindowSize().y, _scene));
		runTracer(tracer);
	}

	void GLEmbreeTracer::whittedTracer(int recursions)
	{
		auto tracer = std::unique_ptr<RayTracer>(new WhittedTracer(getWindowSize().x, getWindowSize().y, _scene, recursions));
		runTracer(tracer);
	}

	void GLEmbreeTracer::runTracer(std::unique_ptr<RayTracer>& tracer) {
		auto start = std::chrono::high_resolution_clock::now();

		std::cout << "Starting tracing with " << threads << " threads..." << std::endl;
		int x = getWindowSize().x;
		float widthPerThread = (x / (float)threads);

		std::vector<std::future<float*>> futures;
		std::vector<int> imageSizes;
		for (int i = 0; i < threads; i++) {
			int start = (int)(i * widthPerThread);
			int end = (int)(i * widthPerThread + widthPerThread);
			imageSizes.push_back((end - start) * getWindowSize().x * 3);
			futures.push_back(tracer->start(cam, 1, start, end));
		}

		std::vector<float*> result;
		for (auto& e : futures) {
			result.push_back(e.get());
		}

		float* image = new float[getWindowSize().x * getWindowSize().y * 3];
		int loc = 0;
		for (int i = 0; i < result.size(); i++) {
			memcpy(image + loc, result[i], imageSizes[i] * sizeof(float));
			loc += imageSizes[i];
		}

		if (this->imageFormat == 0) {
			ImageSaver::saveImageAsPPM(this->getPathToExecutable() + "../../" + tracedFileName, getWindowSize().x, getWindowSize().y, image);
		}
		else {
			ImageSaver::saveImageAsPNG(this->getPathToExecutable() + "../../" + tracedFileName, getWindowSize().x, getWindowSize().y, image);
		};

		delete[] image;

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		std::cout << "Raytracing took " << duration.count() << " seconds..." << std::endl;
	}
}

