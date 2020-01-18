#include "Scene.h"

#include "GLEmbreeTracer.h"
#include <cmath>

namespace cgCourse {
    
    void embree_error(void * ptr, RTCError error, const char * str)
    {
        fprintf(stderr, "EMBREE ERROR: %s\n", str);
    }
    
    Scene::Scene(){
        device = rtcNewDevice(NULL);
        rtcSetDeviceErrorFunction(device, embree_error, NULL);
        
        scene = rtcNewScene(device);
    }
    
    Scene::~Scene(){
        rtcReleaseScene(scene);
        rtcReleaseDevice(device);
    }

    void Scene::add_positional_light(const unsigned& id, color c, vector3 pos){
        posLights.push_back(new positional_light(id, c, pos));
        
        auto drawable = new Sphere(glm::vec4(pos.toGlm(), 0.05));
        
        drawable->createVertexArray(0, 1, 2, 3, 4);
        drawables.push_back(drawable);
    }
    
    void Scene::add_directional_light(const unsigned & id, color c, vector3 pos){
    }
    
    void Scene::add_circular_area_light(const unsigned& id, color c, vector3 pos, float r){
    }
    
    void Scene::add_rectangular_area_light(const unsigned& id, color c, vector3 pos, vector3 h, vector3 v){
    }
    
    void Scene::add_diffuse_material(const unsigned& id, color d){
		
		auto mat = std::make_shared<Material>();
		mat->ka = glm::vec3(0.3);
		mat->kd = d.toGlm();
		mat->ks = glm::vec3(0);
		mat->ns = 0;

		materials[id] = mat;
    }
    
    void Scene::add_specular_material(const unsigned& id, color s, float n){

		auto mat = std::make_shared<Material>();
		mat->ka = glm::vec3(0.3);
		mat->kd = glm::vec3(0);
		mat->ks = s.toGlm();
		mat->ns = n;

		materials[id] = mat;
    }
    
    void Scene::add_mixed_material(const unsigned& id, color d, color s, float n){

		auto mat = std::make_shared<Material>();
		mat->ka = glm::vec3(0.3);
		mat->kd = d.toGlm();
		mat->ks = s.toGlm();
		mat->ns = n;

		materials[id] = mat;
    }
    
    void Scene::add_sphere_object(const unsigned& id, unsigned mat_id, vector3 pos, float r){
		auto xyzr = glm::vec4(pos.x, pos.y, pos.z, r);
		
		embree2DrawableShapeIndex[add_sphere(xyzr)] = drawables.size();

		auto drawable = new Sphere(xyzr);
		drawable->createVertexArray(0, 1, 2, 3, 4);

		drawable->setMaterial(materials[mat_id]);
		drawables.push_back(drawable);
    }
    
    void Scene::add_mesh_object(const unsigned& id, unsigned mat_id, std::string f, std::string path){
       
		auto drawable = new Mesh();
		drawable->createVertexArray(0, 1, 2, 3, 4);
		drawable->load(path, f, true, false, true);
		drawable->setPosition(glm::vec3(0.0));
		drawable->setScaling(glm::vec3(1.0));
		drawable->setMaterial(materials[mat_id]);
		
		embree2DrawableShapeIndex[add_mesh(*drawable->elements[0], drawable->getModelMatrix())] = drawables.size();
        
        drawables.push_back(drawable);
    }

	void Scene::add_room_object(const unsigned& id, unsigned mat_id, float scale, vector3 pos) {

		auto drawable = new Room();
		drawable->createVertexArray(0, 1, 2, 3, 4);
		drawable->setScaling(glm::vec3(scale));
		drawable->setPosition(pos.toGlm());
		drawable->setMaterial(materials[mat_id]);

		embree2DrawableShapeIndex[add_mesh(*drawable, drawable->getModelMatrix())] = drawables.size();
		
		drawables.push_back(drawable);
	}
    
    RTCScene Scene::getRTCScene(){
        return scene;
    }
    
    void Scene::CommitScene(GLEmbreeTracer* tracer){
		rtcCommitScene(scene);
    }

	void Scene::draw(const glm::mat4& _projectionMatrix, const glm::mat4& _viewMatrix, std::shared_ptr<ShaderProgram> _shaderProgram) {
		for (int i = 0; i < drawables.size(); i++) {
			drawables[i]->draw(_projectionMatrix, _viewMatrix, _shaderProgram);
		}
	}

	void Scene::addLightVariables(const std::shared_ptr<ShaderProgram>& _program) {
		int lightCount = 0;

		for (int i = 0; i < posLights.size(); i++) {
			auto pos_light = static_cast<positional_light*>(posLights[i]);

			if (pos_light != nullptr) {
				auto startString = std::string("lights[") + std::to_string(lightCount) + std::string("]");
				_program->setUniform3fv(startString + std::string(".position"), pos_light->position.toGlm());
				_program->setUniform3fv(startString + std::string(".ambient"), glm::vec3(0.4));
				_program->setUniform3fv(startString + std::string(".diffuse"), pos_light->intensity.toGlm());
				_program->setUniform3fv(startString + std::string(".specular"), pos_light->intensity.toGlm());
				lightCount++; 
			}
		}
		std::cout << "lightcount " << lightCount << std::endl;
		_program->setUniformi("lightCount", lightCount);
	}
    
    glm::vec3 Scene::shadeLocal(ray_hit &r, bool shadows){
        
        glm::vec3 output = glm::vec3(0,0,0);
        
        auto mat = drawables[embree2DrawableShapeIndex[r.hit.geomID]]->getMaterial();
        
        //positional lights
        for (int i = 0; i < posLights.size(); i++){
            
            glm::vec3 lightDir = glm::normalize(posLights[i]->position.toGlm() - r.intersectPos());
            glm::vec3 lightColor = posLights[i]->intensity.toGlm();
            
            //diffuse
            float diff = glm::max(glm::dot(r.normal(), lightDir), 0.0f);
            auto diffuse = lightColor * diff * mat->kd;
            
            //specular
            //auto reflectDir = glm::reflect(-lightDir, r.normal());
            
            auto viewDir = glm::normalize(glm::normalize(r.org() - r.intersectPos()));
            auto halfWayDir = glm::normalize(lightDir + viewDir);
            float spec = glm::pow(glm::max(glm::dot(r.normal(), halfWayDir), 0.0f), mat->ns);
            auto specular = lightColor * spec * mat->ks;
            
			//shadows
			bool shadowed = false;

			if (shadows) {
				auto shadowRayDir = posLights[i]->position.toGlm() - r.intersectPos();
				auto shadowRayDirN = glm::normalize(shadowRayDir);

				auto ray = ray_hit(r.intersectPos() + (shadowRayDirN * 0.001f), shadowRayDirN);
				if (intersect(ray)) {

					auto hitVector = ray.intersectPos() - ray.org();

					if (glm::length(hitVector) < glm::length(shadowRayDir)) {
						shadowed = true;
					}
				}
			}
			output += (1.0f - shadowed) * (diffuse + specular);
        }

        return output;
    }
    
    glm::vec3 Scene::shadeWhitted(ray_hit &r, int n){
        glm::vec3 output = glm::vec3(0,0,0);
		
		output += shadeLocal(r, true);

		if (n == 0) {
			return output;
		}

		auto mat = drawables[embree2DrawableShapeIndex[r.hit.geomID]]->getMaterial();
		
		auto reflected = glm::normalize(glm::reflect(r.dir(), r.normal()));

		auto reflected_ray = ray_hit(r.intersectPos() + (reflected * 0.001f), reflected);
		if (intersect(reflected_ray)) {
			output += (1.0f * mat->ks) * shadeWhitted(reflected_ray, n - 1);
		}
        
        return output;
    }
    
    unsigned Scene::add_sphere(const glm::vec4 & xyzr)
    {
        RTCGeometry geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_SPHERE_POINT);
        
        glm::vec4 * pxyzr = (glm::vec4 *) rtcSetNewGeometryBuffer(geom,
                                                                  RTC_BUFFER_TYPE_VERTEX, 0,
                                                                  RTC_FORMAT_FLOAT4, 4 * sizeof(float), 1);
        *pxyzr = xyzr;
        
        rtcCommitGeometry(geom);
        
        unsigned geom_id = rtcAttachGeometry(scene, geom);
        rtcReleaseGeometry(geom);
        
        return geom_id;
    }
    
    unsigned Scene::add_mesh(const DrawableShape & mesh, const glm::mat4 & model_matrix)
    {
        RTCGeometry geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
        
        const std::vector<glm::vec3> & positions = mesh.getPositions();
        glm::vec3 * vertices = (glm::vec3 *) rtcSetNewGeometryBuffer(geom,
                                                                     RTC_BUFFER_TYPE_VERTEX, 0,
                                                                     RTC_FORMAT_FLOAT3, 3 * sizeof(float),
                                                                     positions.size());
        
        const std::vector<glm::uvec3> & faces = mesh.getFaces();
        glm::uvec3 * tri_idxs = (glm::uvec3 *) rtcSetNewGeometryBuffer(geom,
                                                                       RTC_BUFFER_TYPE_INDEX, 0,
                                                                       RTC_FORMAT_UINT3, 3 * sizeof(int),
                                                                       faces.size());
        
        for(unsigned i = 0; i < positions.size(); i++)
            vertices[i] = glm::vec3(model_matrix * glm::vec4(positions[i], 1.f));
        
        for(unsigned i = 0; i < faces.size(); i++)
            tri_idxs[i] = faces[i];
        
        rtcCommitGeometry(geom);
        
        unsigned geom_id = rtcAttachGeometry(scene, geom);
        rtcReleaseGeometry(geom);
        
        return geom_id;
    }

	unsigned Scene::add_room(const Room & room, const glm::mat4 & model_matrix)
	{
		RTCGeometry geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

		const std::vector<glm::vec3> & positions = room.getPositions();
		glm::vec3 * vertices = (glm::vec3 *) rtcSetNewGeometryBuffer(geom,
			RTC_BUFFER_TYPE_VERTEX, 0,
			RTC_FORMAT_FLOAT3, 3 * sizeof(float),
			positions.size());

		const std::vector<glm::uvec3> & faces = room.getFaces();
		glm::uvec3 * tri_idxs = (glm::uvec3 *) rtcSetNewGeometryBuffer(geom,
			RTC_BUFFER_TYPE_INDEX, 0,
			RTC_FORMAT_UINT3, 3 * sizeof(int),
			faces.size());

		for (unsigned i = 0; i < positions.size(); i++)
			vertices[i] = glm::vec3(model_matrix * glm::vec4(positions[i], 1.f));

		for (unsigned i = 0; i < faces.size(); i++)
			tri_idxs[i] = faces[i];

		rtcCommitGeometry(geom);

		unsigned geom_id = rtcAttachGeometry(scene, geom);
		rtcReleaseGeometry(geom);

		return geom_id;
	}

    bool Scene::intersect(ray_hit &r){
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        rtcIntersect1(scene, &context, &r);
        
        return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    }
}
