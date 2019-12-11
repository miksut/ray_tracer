#ifndef Example_Sphere_h
#define Example_Sphere_h

#include "DrawableShape.h"

namespace cgCourse
{
	class Sphere : public DrawableShape
	{
	public:
		Sphere(const glm::vec4 & _xyzr = {0,0,0,1}, const int & res = 25);
        
		glm::vec4 xyzr;
	};
}

#endif
