#include "Scene.h"

#include "GLEmbreeTracer.h"

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
        elements.push_back(new positional_light(id, c, pos));
    }
    
    void Scene::add_directional_light(const unsigned & id, color c, vector3 pos){
        elements.push_back(new directional_light(id, c, pos));
    }
    
    void Scene::add_circular_area_light(const unsigned& id, color c, vector3 pos, float r){
        elements.push_back(new circular_area_light(id, c, pos, r));
    }
    
    void Scene::add_rectangular_area_light(const unsigned& id, color c, vector3 pos, vector3 h, vector3 v){
        elements.push_back(new rectangular_area_light(id, c, pos, h, v));
    }
    
    void Scene::add_diffuse_material(const unsigned& id, color d){
        elements.push_back(new diffuse_material(id, d));
    }
    
    void Scene::add_specular_material(const unsigned& id, color s, float n){
        elements.push_back(new specular_material(id, s, n));
    }
    
    void Scene::add_mixed_material(const unsigned& id, color d, color s, float n){
        elements.push_back(new mixed_material(id, d, s, n));
    }
    
    void Scene::add_sphere_object(const unsigned& id, unsigned mat_id, vector3 pos, float r){
        elements.push_back(new sphere_object(id, mat_id, pos, r));
    }
    
    void Scene::add_mesh_object(const unsigned& id, unsigned mat_id, std::string f){
        elements.push_back(new mesh_object(id, mat_id, f));
    }
    
    RTCScene Scene::getRTCScene(){
        return scene;
    }
    
    void Scene::InitializeViewPort(GLEmbreeTracer* tracer){
        //...
        
        add_sphere(tracer->sphere->xyzr);
        add_mesh(*tracer->cube, tracer->cube->getModelMatrix());
        rtcCommitScene(scene);
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
    
    
}
