#pragma once

#include "player.h"

struct GameCache
{
    std::unique_ptr<Player> player_;
};