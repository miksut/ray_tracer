#ifndef WhittedTracer_h
#define WhittedTracer_h

#include "RayTracer.h"

namespace cgCourse {
    
    // Base Tracer class which can anti alias with samples, and run whitted ray tracing or simple raycasting
    class BaseTracer : public RayTracer {
    public:
		BaseTracer(int width, int height, std::shared_ptr<Scene> scene, int recursions, bool aa, bool whitted) : RayTracer(width, height, scene), recursions(recursions), antiAliasing(aa), whitted(whitted) {};
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples, int startY, int endY);
    private:
        
        static float* trace(const Camera & cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned & samples, int recursions, bool aa, bool whitted, int startY, int endY);
        static bool intersect(RTCScene scene, ray_hit & r);

		int recursions; // amount of recursions for whitted
        bool antiAliasing; // bool if anti Aliasing
        bool whitted; // bool if doing whitted-style raytracing
    };
}

#endif
