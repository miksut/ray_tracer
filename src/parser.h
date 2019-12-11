#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

struct scene
{
	//std::vector<> lights;
	//std::vector<> materials;
	//std::vector<> objects;

	void add_possitional_light(...) { /* COMPLETE */ };
	void add_directional_light(...) { /* COMPLETE */ };
	void add_circular_area_light(...) { /* COMPLETE */ };
	void add_rectangular_area_light(...) { /* COMPLETE */ };
	
	void add_diffuse_material(...) { /* COMPLETE */ };
	void add_specular_material(...) { /* COMPLETE */ };
	void add_mixed_material(...) { /* COMPLETE */ };
	
	void add_sphere_object(...) { /* COMPLETE */ };
	void add_mesh_object(...) { /* COMPLETE */ };
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

