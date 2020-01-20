#include "RayTracer.h"

namespace cgCourse {
    RayTracer::RayTracer(int width, int height, std::shared_ptr<Scene> scene, int aa) : width(width), height(height), scene(scene), antiAliasing(aa){
    }
}
