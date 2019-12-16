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
#include "Mesh.h"
#include "FrameBuffer.h"


namespace cgCourse
{
  class GLEmbreeTracer : public GLApp
  {
    public:
      enum LightMotionMode {
        Forward = 0, Backward  = 1
      };

      GLEmbreeTracer(glm::uvec2 _windowSize, std::string _title, std::string _exepath);

      bool init() override;
      bool update(double dt) override;
      bool render() override;
      bool end() override;
      void tracer();

      LightInfo light;
    private:
      void addLightVariables(const std::shared_ptr<ShaderProgram>& _program);

      std::shared_ptr<ShaderProgram> programForMeshPhong;
      std::shared_ptr<ShaderProgram> programForMeshCook;
      std::shared_ptr<ShaderProgram> programForMeshBlinn;
      std::shared_ptr<ShaderProgram> activeProgram;

      std::shared_ptr<Sphere> sphere;
      std::shared_ptr<Cube> cube;
      std::shared_ptr<Cube> lightbox;

      std::shared_ptr<Texture> cubetex;
      std::shared_ptr<Texture> cubetexSpec;
      std::shared_ptr<Texture> cubeNormaltex;


      float animation;
      LightMotionMode animationDir;

      glm::mat4 mvpMatrix=glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

      Camera cam;

      int shadingAlgorithm = 0; //phong, blinn, cook
      //   bool inputAccept;
      float pointSize = 40;
  };
}

#endif
