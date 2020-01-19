#ifndef Scene_h
#define Scene_h

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <future>
#include <map>

#include <embree3/rtcore.h>
#include "DrawableShape.h"
#include "Camera.h"

#include "Room.h"
#include "Light.h"

namespace cgCourse {
    
    struct ray_hit: public RTCRayHit
    {
        ray_hit(const glm::vec3& origin = glm::vec3(0.0f),
                const glm::vec3& direction = glm::vec3(0.0f),
                float near = 0.0f,
                float far = FLT_MAX)
        {
            ray.org_x = origin.x;
            ray.org_y = origin.y;
            ray.org_z = origin.z;
            ray.tnear = near;
            
            ray.dir_x = direction.x;
            ray.dir_y = direction.y;
            ray.dir_z = direction.z;
            ray.time = 0.0f;
            
            ray.tfar = far;
            ray.mask = 0;
            ray.flags = 0;
            
            //hit.primID = RTC_INVALID_GEOMETRY_ID;
            hit.geomID = RTC_INVALID_GEOMETRY_ID;
            hit.instID[0] = RTC_INVALID_GEOMETRY_ID;
        }
        
        void org(const glm::vec3& origin)
        {
            ray.org_x = origin.x;
            ray.org_y = origin.y;
            ray.org_z = origin.z;
        }
        
        const glm::vec3 org() const
        {
            return {ray.org_x, ray.org_y, ray.org_z};
        }
        
        void dir(const glm::vec3& direction)
        {
            ray.dir_x = direction.x;
            ray.dir_y = direction.y;
            ray.dir_z = direction.z;
        }
        
        const glm::vec3 dir() const
        {
            return glm::normalize(glm::vec3(ray.dir_x, ray.dir_y, ray.dir_z));
        }
        
        const glm::vec3 normal() const
        {
            return glm::normalize(glm::vec3(hit.Ng_x, hit.Ng_y, hit.Ng_z));
        }
        
        const glm::vec3 intersectPos() const
        {
            return org() + ray.tfar * dir();
        }
    };

    struct color
    {
        color(float r, float g, float b) : r(r), g(g), b(b) {};
        const float r, g, b;

		glm::vec3 toGlm() const {
			return glm::vec3(r, g, b);
		}
    };

    struct vector3
    {
        vector3(float x, float y, float z) : x(x), y(y), z(z) {};
        const float x, y, z;

		glm::vec3 toGlm() const {
			return glm::vec3(x, y, z);
		}
    };

    struct light
    {
        light(const unsigned int id) : id(id) {};
        const unsigned id;
    };

    // lights

    struct directional_light : light
    {
        directional_light(const unsigned int id, color i, vector3 d) : light(id), intensity(i), direction(d) {};
        const color intensity;
        const vector3 direction;
    };

    struct circular_area_light : light
    {
        circular_area_light(const unsigned int id, color i, vector3 p, float r) : light(id), intensity(i), position(p), radius(r) {};
        const color intensity;
        const vector3 position;
        const float radius;
    };

    struct rectangular_area_light : light
    {
        rectangular_area_light(const unsigned int id, color i, vector3 p, vector3 h, vector3 v) : light(id), intensity(i), position(p), horizontal_half_axis(h), vertical_half_axis(v) {};
        const color intensity;
        const vector3 position;
        
        const vector3 horizontal_half_axis;
        const vector3 vertical_half_axis;
    };

    class GLEmbreeTracer;
    class Scene {
        RTCDevice device;
        RTCScene scene;
    public:
        Scene();
        ~Scene();
        
        void add_positional_light(const unsigned& id, color c, vector3 pos);
        
        void add_directional_light(const unsigned & id, color c, vector3 dir);
        
        void add_circular_area_light(const unsigned& id, color c, vector3 pos, float r);
        
        void add_rectangular_area_light(const unsigned& id, color c, vector3 pos, vector3 h, vector3 v);
        
        void add_diffuse_material(const unsigned& id, color d);
        
        void add_specular_material(const unsigned& id, color s, float n);
        
        void add_mixed_material(const unsigned& id, color d, color s, float n);
        
        void add_sphere_object(const unsigned& id, unsigned mat_id, vector3 pos, float r);
        
        void add_mesh_object(const unsigned& id, unsigned mat_id, std::string f, std::string path, vector3 pos, float scale);

		void add_room_object(const unsigned& id, unsigned mat_id, float scale, vector3 pos, vector3 col, std::vector<float> element);
        
        void CommitScene(GLEmbreeTracer* tracer);
        
        RTCScene getRTCScene();
		
		void draw(const glm::mat4& _projectionMatrix, const glm::mat4& _viewMatrix, std::shared_ptr<ShaderProgram> _shaderProgram);
		
		void addLightVariables(const std::shared_ptr<ShaderProgram>& _program);
        
        glm::vec3 shadeLocal(ray_hit &r, bool shadows);
        glm::vec3 shadeWhitted(ray_hit &r, int n);
        
	private:
        unsigned add_sphere(const glm::vec4 & xyzr);
        unsigned add_mesh(const DrawableShape & mesh, const glm::mat4 & model_matrix = glm::mat4());
		bool intersect(ray_hit &r);
        
		std::map<unsigned, unsigned> embree2DrawableShapeIndex;

		std::vector<DrawableShape*> drawables;
		std::map<unsigned, std::shared_ptr<Material>> materials; //maps scene id to material
        
		std::vector<directional_light*> dirLights;
		SampleAmount sampleAmount = SampleAmount::Low;
	};
    
}

#endif /* Scene_hpp */
