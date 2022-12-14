#ifndef GLEmbreeTracer_h
#define GLEmbreeTracer_h

#include "GLApp.h"
#include "Sphere.h"
#include "Cube.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Texture.h"
#include "ImageSaver.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <future>
#include "Mesh.h"
#include "FrameBuffer.h"

#include "parser.h"
#include "RayTracer.h"

namespace cgCourse
{
  class GLEmbreeTracer : public GLApp
  {
    public:
      // how to save the image (format)
	  enum ImageFormat {
		  PPM = 0, PNG = 1
	  };

      GLEmbreeTracer(glm::uvec2 _windowSize, std::string _title, std::string _exepath);

      bool init() override;
      bool update(double dt) override;
      bool render() override;
      bool end() override;
      
      // loads a scene into our _scene field (it has to be in the res/scene folder
	  void loadScene(char* sceneName);
      
      //each raytracer gets its own function (they call each runTracer)
      void rayCaster(bool antiAliasing);
      void whittedTracer(bool antiAliasing, int recursions);
      
    private:
      std::shared_ptr<ShaderProgram> programForMeshPhong;
      std::shared_ptr<ShaderProgram> programForMeshBlinn;
      std::shared_ptr<ShaderProgram> activeProgram;
      
      // parser to read scene file and scene object
      std::shared_ptr<parser> _parser;
      std::shared_ptr<Scene> _scene;
      
      glm::mat4 mvpMatrix=glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
      
      // actual method to run a raytracer
	  void runTracer(RayTracer* tracer);

      Camera cam;

      int shadingAlgorithm = 1; //phong, blinn
	  char tracedFileName[128] = "tracedImage"; //filename of the image to be saved
	  ImageFormat imageFormat = ImageFormat::PNG; // image format for image to be saved
	  int threads = 4; // threads to use for raytracing
      int samplesAA = 4; // samples to use for anti aliasing
      bool notificationSounds = false; // to have notification sounds when raytracing ended
  };
}

#endif
