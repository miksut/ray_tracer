#include "Room.h"

namespace cgCourse
{
	Room::Room(std::vector<float> element, std::shared_ptr<Material> mat) : DrawableShape()
	{
		// set geometry with respect to local origin
		this->positions = {
			{ element[0], element[1], element[2] },   // index 0
			{ element[3], element[4], element[5] },
			{ element[6], element[7], element[8] },
			{ element[9], element[10], element[11] }
		};

		this->colors = {

			{ mat->kd.r + mat->ka.r, mat->kd.g + mat->ka.g, mat->kd.b + mat->ka.b },
			{ mat->kd.r + mat->ka.r, mat->kd.g + mat->ka.g, mat->kd.b + mat->ka.b },
			{ mat->kd.r + mat->ka.r, mat->kd.g + mat->ka.g, mat->kd.b + mat->ka.b },
			{ mat->kd.r + mat->ka.r, mat->kd.g + mat->ka.g, mat->kd.b + mat->ka.b }
		};

		this->normals = {
			{ element[12], element[13], element[14] },
			{ element[12], element[13], element[14] },
			{ element[12], element[13], element[14] },
			{ element[12], element[13], element[14] }
		};

		this->texCoords = {
			{ element[15], element[16] },
			{ element[17], element[18] },
			{ element[19], element[20] },
			{ element[21], element[22] },
		};

		this->faces = {
			{ element[23], element[24], element[25] }, { element[26], element[27], element[28] },
		};

		this->faceNormals = {
			{ element[29], element[30], element[31] }, { element[32], element[33], element[34] },
		};
        
        this->primitiveType = triangle;
        
        this->setMaterial(std::make_shared<Material>());
	}
}
