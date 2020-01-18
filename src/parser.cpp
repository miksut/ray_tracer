#include "parser.h"

#include <iostream>
#include <memory>

namespace cgCourse {
    using namespace std;
    
    
    parser::parser(GLEmbreeTracer* tracer, const std::string & _pathToExe, std::string pathToFile) {
        
        scene = std::make_shared<Scene>();
        
		this->pathToExe = _pathToExe;
		std::string file = _pathToExe + pathToFile;
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
        
        scene->CommitScene(tracer);
        is.close();
    }
    
    std::shared_ptr<Scene> parser::getScene(){
        return this->scene;
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
            scene->add_positional_light(id, color(ir, ig, ib), vector3(x, y, z));
        }
        
        if(token == "D")
        {
            scene->add_directional_light(id, color(ir, ig, ib), vector3(x, y, z));
        }
        
        if(token == "AC")
        {
            ss >> r;
            scene->add_circular_area_light(id, color(ir, ig, ib), vector3(x, y, z), r);
        }
        
        if(token == "AR")
        {
            ss >> ux >> uy >> uz >> vx >> vy >> vz;
            scene->add_rectangular_area_light(id, color(ir, ig, ib), vector3(x, y, z), vector3(ux, uy, uz), vector3(vx, vy, vz));
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
            scene->add_diffuse_material(id, color(dr, dg, db));
        }
        
        if(token == "S")
        {
            ss >> sr >> sg >> sb >> n;
            scene->add_specular_material(id, color(sr, sg, sb), n);
        }
        
        if(token == "B")
        {
            ss >> dr >> dg >> db >> sr >> sg >> sb >> n;
            scene->add_mixed_material(id, color(dr, dg, db), color(sr, sg, sb), n);
        }
    }
    
    void parser::load_object(const unsigned & id)
    {
        fprintf(stderr, "LOADING Object %d\n", id);
        
        string token, filename;
        unsigned id_mat, id_mat1, id_mat2, id_mat3, id_mat4;
        float x, y, z, r;
		float scale, rd, gr, bl;
        
        read_line();
        ss >> id_mat;
        
        read_line();
        ss >> token;
        
        if(token == "S")
        {
            ss >> x >> y >> z >> r;
            scene->add_sphere_object(id, id_mat, vector3(x, y, z), r);
        }
        
        if(token == "M")
        {
            ss >> filename;
            scene->add_mesh_object(id, id_mat, filename, this->pathToExe + "../../res/PLY/");
        }

		if (token == "R")
		{
			ss >> scale >> x >> y >> z >> rd >> gr >> bl;
			read_line();
			ss >> id_mat1 >> id_mat2 >> id_mat3 >> id_mat4;
			std::vector<unsigned> id_mats = { id_mat, id_mat1, id_mat2, id_mat3, id_mat4 };

			auto room = new RoomElements;
			std::map<int, std::vector<float>> int2roomElement;
			int2roomElement.insert(pair<int, std::vector<float>>(0, room->element0));
			int2roomElement.insert(pair<int, std::vector<float>>(1, room->element1));
			int2roomElement.insert(pair<int, std::vector<float>>(2, room->element2));
			int2roomElement.insert(pair<int, std::vector<float>>(3, room->element3));
			int2roomElement.insert(pair<int, std::vector<float>>(4, room->element4));
			std::map<int, std::vector<float>>::iterator it;

			for (it = int2roomElement.begin(); it != int2roomElement.end(); it++) {
				scene->add_room_object(id+it->first, id_mats[it->first], scale, vector3(x,y,z), vector3(rd,gr,bl), it->second);
			}
		}
    }
    
    bool parser::read_line()
    {
        if(!getline(is, line))
            return false;
        
        ss.clear(); ss.str(line);
        
        return true;
    }
}
