#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <string>
#include <memory>

#include "Scene.h"


namespace cgCourse {
    class GLEmbreeTracer;
    class parser
    {
    private:
        
        std::string line;
        std::ifstream is;
        std::istringstream ss;
        
    public:
        parser(GLEmbreeTracer* tracer, const std::string & file);
        //scene * operator () (const std::string & file); // functor: parse the input file
        
    private:
        std::shared_ptr<Scene> scene;
        
        
        void load_light(const unsigned & id);
        void load_material(const unsigned & id);
        void load_object(const unsigned & id);
        
        bool read_line(); // update line and ss
    };
}

#endif // PARSER_H

