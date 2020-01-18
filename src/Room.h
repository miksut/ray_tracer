#ifndef Example_Room_h
#define Example_Room_h

#include "DrawableShape.h"
#include "Scene.h"

namespace cgCourse
{
	class Room : public DrawableShape
	{
	public:
		Room(std::vector<float> element, std::shared_ptr<Material> mat);
	};
}

#endif
