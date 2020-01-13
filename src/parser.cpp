#include "parser.h"


using namespace std;


parser::parser(): sc(nullptr) {}

scene * parser::operator () (const std::string & file)
{
	sc = new scene;

	string token;
	unsigned id;
	
	is.open(file);
	
	while(read_line())
	{
		ss >> token;
		
		if(token == "#") continue;

		ss >> id;
		if(token == "L") load_light(id);
		if(token == "M") load_material(id);
		if(token == "O") load_object(id);

		token = "";
	}

	is.close();
	
	return sc;
}

void parser::load_light(const unsigned & id)
{
	fprintf(stderr, "LOADING Light %d\n", id);
	
	string token;
	float ir, ig, ib, x, y, z, r, ux, uy, uz, vx, vy, vz;

	read_line();
	ss >> ir >> ig >> ib;
	
	read_line();
	ss >> token >> x >> y >> z;

	if(token == "P")
	{
		sc->add_positional_light(id, color(ir, ig, ib), vector3(x, y, z));
	}
	
	if(token == "D")
	{
		sc->add_directional_light(id, color(ir, ig, ib), vector3(x, y, z));
	}
	
	if(token == "AC")
	{
		ss >> r;
		sc->add_circular_area_light(id, color(ir, ig, ib), vector3(x, y, z), r);
	}

	if(token == "AR")
	{
		ss >> ux >> uy >> uz >> vx >> vy >> vz;
		sc->add_rectangular_area_light(id, color(ir, ig, ib), vector3(x, y, z), vector3(ux, uy, uz), vector3(vx, vy, vz));
	}
}

void parser::load_material(const unsigned & id)
{
	fprintf(stderr, "LOADING Material %d\n", id);

	string token;
	float dr, dg, db, sr, sg, sb, n;
	
	read_line();
	ss >> token;
	
	if(token == "D")
	{
		ss >> dr >> dg >> db;
		sc->add_diffuse_material(id, color(dr, dg, db));
	}
	
	if(token == "S")
	{
		ss >> sr >> sg >> sb >> n;
		sc->add_specular_material(id, color(sr, sg, sb), n);
	}
	
	if(token == "B")
	{
		ss >> dr >> dg >> db >> sr >> sg >> sb >> n;
		sc->add_mixed_material(id, color(dr, dg, db), color(sr, sg, sb), n);
	}
}

void parser::load_object(const unsigned & id)
{
	fprintf(stderr, "LOADING Object %d\n", id);

	string token, filename;
	unsigned id_mat;
	float x, y, z, r;

	read_line();
	ss >> id_mat;
	
	read_line();
	ss >> token;
	
	if(token == "S")
	{
		ss >> x >> y >> z >> r;
		sc->add_sphere_object(id, id_mat, vector3(x, y, z), r);
	}
	
	if(token == "M")
	{
		ss >> filename;
		sc->add_mesh_object(id, id_mat, filename);
	}
}

bool parser::read_line()
{
	if(!getline(is, line))
		return false;
	
	ss.clear(); ss.str(line);

	return true;
}

