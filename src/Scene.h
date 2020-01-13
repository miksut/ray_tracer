#ifndef Scene_h
#define Scene_h

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>


namespace cgCourse {
    
    struct color
    {
        color(float r, float g, float b) : r(r), g(g), b(b) {};
        const float r, g, b;
    };

    struct vector3
    {
        vector3(float x, float y, float z) : x(x), y(y), z(z) {};
        const float x, y, z;
    };

    struct scene_element
    {
        scene_element(const unsigned int id) : id(id) {};
        const unsigned id;
    };

    // lights
    struct positional_light : scene_element
    {
        positional_light(const unsigned int id, color i, vector3 p) : scene_element(id), intensity(i), position(p) {};
        const color intensity;
        const vector3 position;
    };

    struct directional_light : scene_element
    {
        directional_light(const unsigned int id, color i, vector3 d) : scene_element(id), intensity(i), direction(d) {};
        const color intensity;
        const vector3 direction;
    };

    struct circular_area_light : scene_element
    {
        circular_area_light(const unsigned int id, color i, vector3 p, float r) : scene_element(id), intensity(i), position(p), radius(r) {};
        const color intensity;
        const vector3 position;
        const float radius;
    };

    struct rectangular_area_light : scene_element
    {
        rectangular_area_light(const unsigned int id, color i, vector3 p, vector3 h, vector3 v) : scene_element(id), intensity(i), position(p), horizontal_half_axis(h), vertical_half_axis(v) {};
        const color intensity;
        const vector3 position;
        
        const vector3 horizontal_half_axis;
        const vector3 vertical_half_axis;
    };

    // materials
    struct diffuse_material : scene_element
    {
        diffuse_material(const unsigned int id, color d) : scene_element(id), diffuse(d) {};
        const color diffuse;
    };

    struct specular_material : scene_element
    {
        specular_material(const unsigned int id, color spec, float s) : scene_element(id), specular(spec), shininess(s) {};
        const color specular;
        const float shininess;
    };

    struct mixed_material : scene_element
    {
        mixed_material(const unsigned int id, color d, color spec, float s) : scene_element(id), diffuse(d), specular(spec), shininess(s) {};
        //diffuse + specular = [1,1,1] has to hold!
        const color diffuse;
        const color specular;
        const float shininess;
    };

    // objects

    struct object : scene_element
    {
        object(const unsigned int id, unsigned mat_id) : scene_element(id), material_id(mat_id) {};
        const unsigned material_id;
    };
    struct sphere_object : object
    {
        sphere_object(const unsigned int id, unsigned mat_id, vector3 pos, float r) : object(id, mat_id), position(pos), radius(r) {};
        const vector3 position;
        const float radius;
    };

    struct mesh_object : object
    {
        mesh_object(const unsigned int id, unsigned mat_id, std::string f) : object(id, mat_id), filename(f) {};
        const std::string filename;
    };
    class GLEmbreeTracer;
    class Scene {
    public:
        Scene(GLEmbreeTracer * tracer);
        
        void add_positional_light(const unsigned& id, color c, vector3 pos);
        
        void add_directional_light(const unsigned & id, color c, vector3 pos);
        
        void add_circular_area_light(const unsigned& id, color c, vector3 pos, float r);
        
        void add_rectangular_area_light(const unsigned& id, color c, vector3 pos, vector3 h, vector3 v);
        
        void add_diffuse_material(const unsigned& id, color d);
        
        void add_specular_material(const unsigned& id, color s, float n);
        
        void add_mixed_material(const unsigned& id, color d, color s, float n);
        
        void add_sphere_object(const unsigned& id, unsigned mat_id, vector3 pos, float r);
        
        void add_mesh_object(const unsigned& id, unsigned mat_id, std::string f);
        
    private:
        std::vector<scene_element*> elements;
    };
    
}


#endif /* Scene_hpp */
