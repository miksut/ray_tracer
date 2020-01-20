#ifndef WhittedTracer_h
#define WhittedTracer_h

#include "RayTracer.h"

namespace cgCourse {
    class BaseTracer : public RayTracer {
    public:
		BaseTracer(int width, int height, std::shared_ptr<Scene> scene, int recursions, bool aa, bool whitted) : RayTracer(width, height, scene), recursions(recursions), antiAliasing(aa), whitted(whitted) {};
        virtual std::future<float*> start(const Camera & cam, const unsigned & samples, int startY, int endY);
    private:
        
        static float* trace(const Camera & cam, std::shared_ptr<Scene> scene, int width, int height, const unsigned & samples, int recursions, bool aa, bool whitted, int startY, int endY);
        static bool intersect(RTCScene scene, ray_hit & r);

		int recursions;
        bool antiAliasing;
        bool whitted;
    };
}

#endif
