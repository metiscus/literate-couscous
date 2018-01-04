#pragma once

#include <cstdint>

class Mapgen
{
    uint32_t width_;
    uint32_t height_;

public:

    Mapgen(uint32_t width, uint32_t height);
};