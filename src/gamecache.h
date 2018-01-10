#pragma once

#include "player.h"
#include "map.h"

struct GameCache
{
    std::unique_ptr<Player> player;
    std::unique_ptr<Map> map;
};