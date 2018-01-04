#include "game.h"

#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <staticjson/staticjson.hpp>

const std::string Game::s_data_path_ = "./data/";

namespace fs = boost::filesystem;

Game::Game()
{
    load_object_blueprints();
}

void Game::load_object_blueprints()
{
    fs::path data_dir (s_data_path_);
    fs::directory_iterator itr(data_dir);
    for(auto entry : itr)
    {
        // For regular files load the file
        if(fs::is_regular_file(entry))
        {
            // Convert the path to a string
            fs::path file = entry;
            std::ifstream infile (file.string());
            std::stringstream ss;
            ss << infile.rdbuf();

            // Then reconstitute the object
            Object obj;
            staticjson::ParseStatus ps;
            staticjson::from_json_string(ss.str().c_str(), &obj, &ps);
            if(ps.has_error())
            {
                std::cerr<<"Failed to parse object file \""<<file.string()<<"\" with error \""<<ps.description()<<"\"\n";
            }
            else
            {
                object_blueprints_[obj.get_id()] = obj.clone();
            }
        }
    }
}
