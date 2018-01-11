#include "game.h"

#include <boost/filesystem.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <staticjson/staticjson.hpp>
#include "race.h"
#include "ui/ui.h"
#include "mainmenustate.h"
#include <glad/glad.h>

const std::string Game::s_data_path_ = "./data/";

namespace fs = boost::filesystem;

namespace {
    std::shared_ptr<Game> g_game;
}

void Game::start()
{
    g_game.reset(new Game());
}

void Game::stop()
{
    g_game.reset();
}

std::shared_ptr<Game> Game::get()
{
    return g_game;
}

Game::Game()
{
    load_object_blueprints();
    load_races();

    // Create Game Window
    sf::VideoMode video_mode (1024, 768);
    
    sf::ContextSettings context(24, 8, 4, 3, 2);
    window_ = std::make_shared<sf::RenderWindow>(video_mode, "Game", sf::Style::Default, context);
    //window_ = std::make_shared<sf::RenderWindow>(video_mode, "Game");
    window_->setActive(true);

    if(!gladLoadGL()) {
        exit(-1);
    }

    ui::initialize(window_);
    
    push_state(std::make_shared<MainMenuState>(this)); 

    cache_ = std::make_shared<GameCache>(); 


    tileset_.load("data/gfx/tileset.txt");
}

#if 0
void Game::new_game()
{

    // Create a character
    // Configure time and weather
    LocationInfo here;
    here.latitude = -50.0f;
    here.max_temperature.a = 4.2f;
    here.max_temperature.b = 13.07f;
    here.min_temperature.a = 3.21f;
    here.min_temperature.b = 12.2f;

    weather_.set_location_info(here);
    weather_.set_time(time_);

    std::cout<<"The date is: "<<time_.get_date()<<"\n";
    std::cout<<"The length of the day is: "<<weather_.get_mean_daylight_hours()<<"\n";
    std::cout<<"The high today is: "<<weather_.compute_day_max_temperature()<<"\n";
    std::cout<<"The low today is: "<<weather_.compute_day_min_temperature()<<"\n";
    
    for(int i=48; i>0; --i)
    {
        std::cout<<"The time is: "<<std::setfill('0')<<std::setw(2)<<time_.hour<<":"<<std::setw(2)<<time_.minute<<":"<<std::setw(2)<<time_.second<<"\n";
        std::cout<<"The current temperature is: "<<weather_.compute_temperature()<<"\n";

        time_.advance(0, 0, 0, 0, 30, 0);
        weather_.set_time(time_);
    }
}
#endif

void Game::run()
{
    // Main game loop
    sf::Clock clock;
    
    while(window_ && window_->isOpen())
    {
        // There is no current state to draw
        if(peek_state() == nullptr)
        {
            continue;
        }
        else 
        {
            // Perform the draw for the current state
            sf::Time elapsed = clock.restart();
            float dt = elapsed.asSeconds();
            
            peek_state()->handle_input();
            peek_state()->update(dt);
            
            window_->clear();
            
            peek_state()->draw(dt);
            
            window_->display();
        }
    }
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

void Game::push_state(GameStatePtr state)
{
    states_.push(state);
}

void Game::pop_state()
{
    states_.pop();
}

void Game::change_state(GameStatePtr state)
{
    if(!states_.empty())
    {
        pop_state();
    }
    push_state(state);
}

GameStatePtr Game::peek_state()
{
    if(states_.empty()) return GameStatePtr();
    else return states_.top();
}

sf::Vector2u Game::get_window_size()
{
    sf::Vector2u ret (0, 0);
    if(window_)
    {
        ret = window_->getSize();
    }
    return ret;
}

TextureManager* Game::get_texture_manager()
{
    return &texture_manager_;
}

std::vector<Race> Game::get_races() const
{
    std::vector<Race> ret;
    for(auto pair : races_)
    {
        ret.push_back(pair.second);
    }

    return ret;
}