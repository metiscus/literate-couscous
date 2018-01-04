#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "object.h"
#include "race.h"
#include "simtime.h"

class Game
{
    static const std::string s_data_path_;
    std::map<uint32_t, ObjectPtr> object_blueprints_;
    std::map<uint32_t, Race> races_;
    
    Simtime time_;

    void load_object_blueprints();
    void load_races();


public:

    Game();

    void new_game();

    void load_game(const std::string& file);
    void save_game(const std::string& file);

};