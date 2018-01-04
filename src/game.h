#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "object.h"

class Game
{
    std::map<uint32_t, ObjectPtr> object_blueprints_;    
    static const std::string s_data_path_;

    void load_object_blueprints();

public:

    Game();

};