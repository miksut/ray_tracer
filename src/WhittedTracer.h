#ifndef WhittedTracer_h
#define WhittedTracer_h

#include "RayTracer.h"

namespace cgCourse {
    class WhittedTracer : public RayTracer {
    public:
        WhittedTracer(int width, int height, std::shared_ptr<Scene> scene) : RayTracer(width, height, scene) {};
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples);
    private:
        
        static float* trace(const Camera & cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned & samples);
        static bool intersect(RTCScene scene, ray_hit & r);
    };
}

#endif
