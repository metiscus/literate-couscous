#pragma once

#include "player.h"
#include "map.h"
#include "world.h"

struct GameCache
{
    GameCache()
        : world(new World())
    {
    }


    std::unique_ptr<World> world;
};