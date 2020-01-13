#include "Scene.h"


namespace cgCourse {
    
    Scene::Scene(GLEmbreeTracer * tracer){
        
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
}
