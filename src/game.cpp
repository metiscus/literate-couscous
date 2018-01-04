#include "game.h"

#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <staticjson/staticjson.hpp>
#include "race.h"

const std::string Game::s_data_path_ = "./data/";

namespace fs = boost::filesystem;

Game::Game()
{
    load_object_blueprints();
    load_races();
}

void Game::new_game()
{
    // Configure time and weather
    LocationInfo here;
    here.latitude = -50.0f;
    here.max_temperature.a = 4.2f;
    here.max_temperature.b = 13.07f;
    here.max_temperature.a = 3.95f;
    here.max_temperature.b = 12.8f;

    weather_.set_location_info(here);
    weather_.set_time(time_);

    std::cout<<"The date is: "<<time_.get_date()<<"\n";
}

void Game::load_game(const std::string& file)
{

}

void Game::save_game(const std::string& file)
{

}

void Game::load_object_blueprints()
{
    fs::path data_dir (s_data_path_);
    data_dir += fs::path ("objects");
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
                std::cerr<<"Loaded object from file \""<<file.string()<<"\"\n";
                object_blueprints_[obj.get_id()] = obj.clone();
            }
        }
    }
}

void Game::load_races()
{
    fs::path data_dir (s_data_path_);
    data_dir += fs::path ("races");
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

            // Then reconstitute the race
            Race obj;
            staticjson::ParseStatus ps;
            staticjson::from_json_string(ss.str().c_str(), &obj, &ps);
            if(ps.has_error())
            {
                std::cerr<<"Failed to parse race file \""<<file.string()<<"\" with error \""<<ps.description()<<"\"\n";
            }
            else
            {
                std::cerr<<"Loaded race from file \""<<file.string()<<"\"\n";
                races_[obj.get_id()] = obj;
            }
        }
    }
}