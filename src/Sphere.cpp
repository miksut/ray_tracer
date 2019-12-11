#include "Sphere.h"
#include <iostream>

// to get M_PI from math libary enable defines
#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
namespace cgCourse
{
	Sphere::Sphere(const glm::vec4 & _xyzr, const int & res) : DrawableShape(), xyzr(_xyzr)
	{
		float r = xyzr[3];
		float delta = M_PI / res;
		for(float phi = 0; phi < 2 * M_PI; phi += delta)
		{
			for(float theta = delta; theta < M_PI; theta += delta)
				positions.push_back(glm::vec3(xyzr) + glm::vec3{r * sin(theta) * cos(phi), r * sin(theta) * sin(phi), r * cos(theta)});

		}
		
		positions.push_back(glm::vec3(xyzr) + glm::vec3{0, 0, r});
		positions.push_back(glm::vec3(xyzr) + glm::vec3{0, 0, -r});

		std::cout << "SPHERE POSITIONS: " << positions.size() << std::endl;
		
		int cols = res - 1;

		int v;
		for(int i = 0; i < 2 * res - 1; i++)
		{
			for(int j = 0; j < cols - 1; j++)
			{
				v = i * cols + j;
				faces.push_back({v, v + 1, v + cols});
				faces.push_back({v + cols, v + 1, v + cols + 1});
			}

			v = i * cols;
			faces.push_back({positions.size() - 2, v, v + cols});
			
			v = (i + 1) * cols - 1;
			faces.push_back({positions.size() - 1, v + cols, v});
		}
		
		for(int j = 0; j < cols - 1; j++)
		{
			v = (2 * res - 1) * cols + j;
			faces.push_back({v + 1, j, v});
			faces.push_back({j + 1, j, v + 1});
		}
		
		v = (2 * res - 1) * cols;
		faces.push_back({positions.size() - 2, v, 0});
		
		v = (2 * res) * cols - 1;
		faces.push_back({positions.size() - 1, cols - 1, v});
		
		std::cout << "SPHERE FACES: " << faces.size() << std::endl;

	/*	
		std::ofstream off("sphere.off");
		off << "OFF\n";
		off << positions.size() << " " << faces.size() << " 0\n";
		
		for(auto v: positions)
			off << v.x << " " << v.y << " " << v.z << "\n";
		
		for(auto f: faces)
			off << "3 " << f.x << " " << f.y << " " << f.z << "\n";
		
		off.close();
	*/
        
		this->setMaterial(std::make_shared<Material>());
        this->primitiveType = triangle;

		// adding face normals
		for (int i = 0; i < this->faces.size(); i++) {
			glm::vec3 v1 = this->positions[this->faces[i].y] - this->positions[this->faces[i].x];
			glm::vec3 v2 = this->positions[this->faces[i].z] - this->positions[this->faces[i].x];
			this->faceNormals.push_back(glm::normalize(glm::cross(v1, v2)));
		}
        
		// adding normals
		for (int i = 0; i < this->positions.size(); i++) {
			std::vector<unsigned int> faceids;
			// find the face ids with this vertex
			for (int j = 0; j < this->faces.size(); j++) {
				if (i == this->faces[j].x || i == this->faces[j].y || i == this->faces[j].z) {
					faceids.push_back(j);
				}	
			}
			// sum up the face normals and divide it by the lenght of the summed up vector
			glm::vec3 vSum(0.0, 0.0, 0.0);
			for (int j = 0; j < faceids.size(); j++) {
				vSum += this->faceNormals[faceids[j]];
			}
			vSum /= glm::length(vSum);
			this->normals.push_back(vSum);
		}
	}
}
