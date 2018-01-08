#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <stack>

#include "gamestate.h"
#include "object.h"
#include "race.h"
#include "simtime.h"
#include "texturemanager.h"
#include "weather.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "gamecache.h"

class Game
{
    static const std::string s_data_path_;
    std::map<uint32_t, ObjectPtr> object_blueprints_;
    std::map<uint32_t, Race> races_;

    std::shared_ptr<sf::RenderWindow> window_;
    
    std::stack<GameStatePtr> states_;

    TextureManager texture_manager_;

    Simtime time_;
    Weather weather_;

    void load_object_blueprints();
    void load_races();

    Game();

    std::shared_ptr<GameCache> cache_;

public:
    // Singleton Commands
    static void start();
    static void stop();
    static std::shared_ptr<Game> get();

    void run();

    void new_game();

    void load_game(const std::string& file);
    void save_game(const std::string& file);

    // State Manager Commands
    void push_state(GameStatePtr state);
    void pop_state();
    void change_state(GameStatePtr state);
    GameStatePtr peek_state();

    // General accessors
    sf::Vector2u get_window_size();

    TextureManager* get_texture_manager();
    
    inline std::shared_ptr<GameCache> get_cache() { return cache_; }

    inline std::shared_ptr<sf::RenderWindow> get_window() { return window_; }

};