#include "Scene.h"

#include "GLEmbreeTracer.h"
#include <cmath>
#include "DrawablePointLight.h"
#include "DrawableRectangularAreaLight.h"
#include "DrawableCircularAreaLight.h"

#include "Gui.h"

namespace cgCourse {
    
    void embree_error(void * ptr, RTCError error, const char * str)
    {
        fprintf(stderr, "EMBREE ERROR: %s\n", str);
    }
    
    Scene::Scene(){
        //init embree
        device = rtcNewDevice(NULL);
        rtcSetDeviceErrorFunction(device, embree_error, NULL);
        
        //connect vars with gui
		connectVar("sampleAmount", &sampleAmount);
        
        //init embree scene
        scene = rtcNewScene(device);
    }
    
    Scene::~Scene(){
        rtcReleaseScene(scene);
        rtcReleaseDevice(device);
    }

    void Scene::add_positional_light(const unsigned& id, color c, vector3 pos){
        auto drawable = new DrawablePointLight(pos.toGlm(), c.toGlm());

        drawable->createVertexArray(0, 1, 2, 3, 4);
        drawableShapes.push_back(drawable);
    }
    
    void Scene::add_directional_light(const unsigned & id, color c, vector3 dir){
		dirLights.push_back(new directional_light(id, c, dir));
    }
    
    void Scene::add_circular_area_light(const unsigned& id, color c, vector3 pos, float r){
		auto drawable = new DrawableCircularAreaLight(pos.toGlm(), c.toGlm(), r);
        
        // add mesh to embree BVH and use the given id for our map (embreeID -> drawableIndex)
		embree2DrawableShapeIndex[add_mesh(*drawable, drawable->getModelMatrix())] = drawableShapes.size();

		drawable->createVertexArray(0, 1, 2, 3, 4);
		drawableShapes.push_back(drawable);
    }
    
    void Scene::add_rectangular_area_light(const unsigned& id, color c, vector3 pos, vector3 h, vector3 v){
		auto drawable = new DrawableRectangularAreaLight(pos.toGlm(), c.toGlm(), h.toGlm(), v.toGlm());
		
        // add mesh to embree BVH and use the given id for our map (embreeID -> drawableIndex)
		embree2DrawableShapeIndex[add_mesh(*drawable, drawable->getModelMatrix())] = drawableShapes.size();

		drawable->createVertexArray(0, 1, 2, 3, 4);
		drawableShapes.push_back(drawable);
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
		
        // add mesh to embree BVH and use the given id for our map (embreeID -> drawableIndex)
		embree2DrawableShapeIndex[add_sphere(xyzr)] = drawableShapes.size();

		auto drawable = new Sphere(xyzr);
		drawable->createVertexArray(0, 1, 2, 3, 4);

		drawable->setMaterial(materials[mat_id]);
		drawableShapes.push_back(drawable);
    }
    
    void Scene::add_mesh_object(const unsigned& id, unsigned mat_id, std::string f, std::string path, vector3 pos, float scale){
       
		auto drawable = new Mesh();
		drawable->createVertexArray(0, 1, 2, 3, 4);
		drawable->load(path, f, true, false, true);
		drawable->setPosition(pos.toGlm());
		drawable->setScaling(glm::vec3(scale));
		drawable->setMaterial(materials[mat_id]);
		
        // add mesh to embree BVH and use the given id for our map (embreeID -> drawableIndex)
		embree2DrawableShapeIndex[add_mesh(*drawable->elements[0], drawable->getModelMatrix())] = drawableShapes.size();
        
        drawableShapes.push_back(drawable);
    }

	void Scene::add_room_object(const unsigned& id, unsigned mat_id, float scale, vector3 pos, vector3 col, std::vector<float> element) {

		auto drawable = new Room(element, materials[mat_id]);
		drawable->createVertexArray(0, 1, 2, 3, 4);
		drawable->setScaling(glm::vec3(scale));
		drawable->setPosition(pos.toGlm());
		drawable->setMaterial(materials[mat_id]);
        
        // add mesh to embree BVH and use the given id for our map (embreeID -> drawableIndex)
		embree2DrawableShapeIndex[add_mesh(*drawable, drawable->getModelMatrix())] = drawableShapes.size();
		
		drawableShapes.push_back(drawable);
	}
    
    RTCScene Scene::getRTCScene(){
        return scene;
    }
    
    void Scene::CommitScene(GLEmbreeTracer* tracer){
		rtcCommitScene(scene);
    }

	void Scene::draw(const glm::mat4& _projectionMatrix, const glm::mat4& _viewMatrix, std::shared_ptr<ShaderProgram> _shaderProgram) {
        
        //loop through drawable Shapes and draw them individually
		for (int i = 0; i < drawableShapes.size(); i++) {
            
            // check if our drawableShape represent a Light
			auto light = dynamic_cast<Light*>(drawableShapes[i]);
			if (light != nullptr) {
                
                // if it is a light, set lightcolor and isLight accordingly
				_shaderProgram->setUniform3fv("lightColor", light->getLightColor());
				_shaderProgram->setUniformi("isLight", true);

				//dont cull lights!
				glDisable(GL_CULL_FACE);
			}
			drawableShapes[i]->draw(_projectionMatrix, _viewMatrix, _shaderProgram);
			
            // enable culling and reset isLight uniform
			glEnable(GL_CULL_FACE);
			_shaderProgram->setUniformi("isLight", false);
		}
	}

	void Scene::addLightVariables(const std::shared_ptr<ShaderProgram>& _program) {
		
		//point lights + area lights
		int lightCount = 0;

		for (int i = 0; i < drawableShapes.size(); i++) {
			auto pos_light = dynamic_cast<SamplableLight*>(drawableShapes[i]);

			if (pos_light != nullptr) {
				auto startString = std::string("lights[") + std::to_string(lightCount) + std::string("]");
				_program->setUniform3fv(startString + std::string(".position"), pos_light->getLightPosition());
				_program->setUniform3fv(startString + std::string(".ambient"), glm::vec3(0.2));
				_program->setUniform3fv(startString + std::string(".diffuse"), pos_light->getLightColor());
				_program->setUniform3fv(startString + std::string(".specular"), pos_light->getLightColor());
				lightCount++; 
			}
		}
		_program->setUniformi("lightCount", lightCount);

		//directional lights
		int dirLightCount = 0;
		for (int i = 0; i < dirLights.size(); i++) {
			auto dir_light = dirLights[i];
			auto startString = std::string("dirLights[") + std::to_string(dirLightCount) + std::string("]");
			_program->setUniform3fv(startString + std::string(".direction"), dir_light->direction.toGlm());
			_program->setUniform3fv(startString + std::string(".ambient"), glm::vec3(0.2));
			_program->setUniform3fv(startString + std::string(".diffuse"), dir_light->intensity.toGlm());
			_program->setUniform3fv(startString + std::string(".specular"), dir_light->intensity.toGlm());
			dirLightCount++;
		}
		_program->setUniformi("dirLightCount", dirLightCount);
	}
    
    glm::vec3 Scene::shadeLocal(ray_hit &r, bool shadows){
        
        glm::vec3 output = glm::vec3(0,0,0);
        
        // get the drawable representing the thing we hit with embree and its material
		auto drawable = drawableShapes[embree2DrawableShapeIndex[r.hit.geomID]];
        auto mat = drawable->getMaterial();
        
        // check if we hit a light
		auto light = dynamic_cast<Light*>(drawable);
		if (light != nullptr) {
            // if we hit a light, we just return lightcolor
			return light->getLightColor();
		}
        
		//directional lights
		for (int i = 0; i < dirLights.size(); i++) {
			glm::vec3 lightDir = -dirLights[i]->direction.toGlm();
			glm::vec3 lightColor = dirLights[i]->intensity.toGlm();

			//diffuse
			float diff = glm::max(glm::dot(r.normal(), lightDir), 0.0f);
			auto diffuse = lightColor * diff * mat->kd;

			//specular
			auto viewDir = glm::normalize(glm::normalize(r.org() - r.intersectPos()));
			auto halfWayDir = glm::normalize(lightDir + viewDir);
			float spec = glm::pow(glm::max(glm::dot(r.normal(), halfWayDir), 0.0f), mat->ns);
			auto specular = lightColor * spec * mat->ks;

			//shadows
			bool shadowed = false;
			if (shadows) {
				auto shadowRayDir = lightDir;
				auto shadowRayDirN = glm::normalize(shadowRayDir);
                
                // start a little bit in correct direction to not create self intersections
				auto ray = ray_hit(r.intersectPos() + (shadowRayDirN * 0.001f), shadowRayDirN);
                
				if (intersect(ray)) {
					shadowed = true;
				}
			}
            
            // add lightinformation if not in shadow
			output += (1.0f - shadowed) * (diffuse + specular);
		}

        //samplable lights (points + area lights)
        for (int i = 0; i < drawableShapes.size(); i++){
            
			auto light = dynamic_cast<SamplableLight*>(drawableShapes[i]);
            
            // if the drawable shape is not a sampleable light, continue loop
			if (light == nullptr)
				continue;
            
            // get the sample positions for each samplable light
			auto samplePositions = light->getSamplePositions(sampleAmount);
            
            // calculate normal point light color
			for (int j = 0; j < samplePositions.size(); j++) {
				glm::vec3 lightDir = glm::normalize(samplePositions[j] - r.intersectPos());
				glm::vec3 lightColor = light->getLightColor();

				//diffuse
				float diff = glm::max(glm::dot(r.normal(), lightDir), 0.0f);
				auto diffuse = lightColor * diff * mat->kd;

				//specular
				auto viewDir = glm::normalize(glm::normalize(r.org() - r.intersectPos()));
				auto halfWayDir = glm::normalize(lightDir + viewDir);
				float spec = glm::pow(glm::max(glm::dot(r.normal(), halfWayDir), 0.0f), mat->ns);
				auto specular = lightColor * spec * mat->ks;

				//shadows
				bool shadowed = false;
				if (shadows) {
					auto shadowRayDir = samplePositions[j] - r.intersectPos();
					auto shadowRayDirN = glm::normalize(shadowRayDir);
                    
                    // start a little bit in correct direction to not create self intersections
					auto ray = ray_hit(r.intersectPos() + (shadowRayDirN * 0.001f), shadowRayDirN);
					if (intersect(ray)) {
						auto hitVector = ray.intersectPos() - ray.org();
                        
                        // if the hit object is farther away than the light => not shadowed
						if (glm::length(hitVector) < glm::length(shadowRayDir)) {
                            // only shadow if not hitting the light itself
                            if (i != embree2DrawableShapeIndex[ray.hit.geomID]){
                                shadowed = true;
                            }
						}
					}
				}
                // add lightinformation if not in shadow (+ divide with amount of samples)
				output += ((1.0f - shadowed) * (diffuse + specular)) / (float) samplePositions.size();
			}
        }

        return output;
    }
    
    glm::vec3 Scene::shadeWhitted(ray_hit &r, int n){
        glm::vec3 output = glm::vec3(0,0,0);
		
        // always add local color first
		output += shadeLocal(r, true);

		if (n == 0) {
            // stop recursion if n == 0
			return output;
		}
        
        // get the drawable representing the thing we hit with embree and its material
		auto drawable = drawableShapes[embree2DrawableShapeIndex[r.hit.geomID]];
		auto mat = drawable->getMaterial();

		auto light = dynamic_cast<Light*>(drawable);
		if (light != nullptr) {
			//dont reflect if we hit a light
			return output;
		}
        
        // reflect ray
		auto reflected = glm::normalize(glm::reflect(r.dir(), r.normal()));
        
        // start ray a little late to not allow self intersections
		auto reflected_ray = ray_hit(r.intersectPos() + (reflected * 0.001f), reflected);
		
        if (intersect(reflected_ray)) {
            // if we hit something then recurse
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

    bool Scene::intersect(ray_hit &r){
        RTCIntersectContext context;
        rtcInitIntersectContext(&context);
        rtcIntersect1(scene, &context, &r);
        
        return r.hit.geomID != RTC_INVALID_GEOMETRY_ID;
    }
}
