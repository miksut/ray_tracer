#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <string>

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

struct scene
{
	//lights
	std::vector<positional_light> positional_lights;
	std::vector<directional_light> directional_lights;
	std::vector<circular_area_light> circular_area_lights;
	std::vector<rectangular_area_light> rectangular_area_lights;

	//materials
	std::vector<diffuse_material> diffuse_materials;
	std::vector<specular_material> specular_materials;
	std::vector<mixed_material> mixed_materials;

	//objects
	std::vector<sphere_object> sphere_objects;
	std::vector<mesh_object> mesh_objects;

	void add_positional_light(const unsigned& id, color c, vector3 pos)
	{
		positional_lights.push_back(positional_light(id, c, pos));
	}

	void add_directional_light(const unsigned & id, color c, vector3 pos) 
	{
		directional_lights.push_back(directional_light(id, c, pos));
	}

	void add_circular_area_light(const unsigned& id, color c, vector3 pos, float r)
	{
		circular_area_lights.push_back(circular_area_light(id, c, pos, r));
	}

	void add_rectangular_area_light(const unsigned& id, color c, vector3 pos, vector3 h, vector3 v)
	{
		rectangular_area_lights.push_back(rectangular_area_light(id, c, pos, h, v));
	}
	
	void add_diffuse_material(const unsigned& id, color d)
	{
		diffuse_materials.push_back(diffuse_material(id, d));
	}

	void add_specular_material(const unsigned& id, color s, float n)
	{
		specular_materials.push_back(specular_material(id, s, n));
	}

	void add_mixed_material(const unsigned& id, color d, color s, float n)
	{
		mixed_materials.push_back(mixed_material(id, d, s, n));
	}
	
	void add_sphere_object(const unsigned& id, unsigned mat_id, vector3 pos, float r)
	{
		sphere_objects.push_back(sphere_object(id, mat_id, pos, r));
	}

	void add_mesh_object(const unsigned& id, unsigned mat_id, std::string f)
	{
		mesh_objects.push_back(mesh_object(id, mat_id, f));
	}
};


class parser
{
	private:
		scene * sc;

		std::string line;
		std::ifstream is;
		std::istringstream ss;

	public:
		parser();
		scene * operator () (const std::string & file); // functor: parse the input file
	
	private:
		void load_light(const unsigned & id);
		void load_material(const unsigned & id);
		void load_object(const unsigned & id);

		bool read_line(); // update line and ss
};

#endif // PARSER_H

