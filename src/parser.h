#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <string>
#include <memory>
#include <map>

#include "Scene.h"


namespace cgCourse {

	struct RoomElements 
	{
			std::vector<float> element0 = { -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0, 3.0, 2.0, 2.0, 1.0, 0.0, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f};
			std::vector<float> element1 = { 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0, 3.0, 2.0, 2.0, 1.0, 0.0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
			std::vector<float> element2 = { -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0, 3.0, 2.0, 2.0, 1.0, 0.0, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f };
			std::vector<float> element3 = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0, 3.0, 2.0, 2.0, 1.0, 0.0, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
			std::vector<float> element4 = { -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0, 3.0, 2.0, 2.0, 1.0, 0.0, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f };
	};

    class GLEmbreeTracer;
    class parser
    {
    private:
        
        std::string line;
        std::ifstream is;
        std::istringstream ss;
        
    public:
        parser(GLEmbreeTracer* tracer, const std::string & _pathToExe, std::string pathToFile);
        std::shared_ptr<Scene> getScene();
        
    private:
        std::shared_ptr<Scene> scene;
        
        void load_light(const unsigned & id);
        void load_material(const unsigned & id);
        void load_object(const unsigned & id);
        
        bool read_line(); // update line and ss

		std::string pathToExe;
    };
}

#endif // PARSER_H

