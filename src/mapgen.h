#pragma once

#include <cstdint>
#include "map.h"
#include <memory>

class Mapgen
{
    uint32_t width_;
    uint32_t height_;
    int32_t depth_;

public:

    Mapgen(uint32_t width, uint32_t height, int32_t depth);

    std::shared_ptr<Map> generate_outdoors_map(uint32_t seed);
};