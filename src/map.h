#pragma once

#include <cstdint>
#include "position.h"
#include <vector>
#include "maptile.h"
#include <staticjson/staticjson.hpp>

class Map
{
    std::vector<MapTile> tiles_;
    uint32_t width_;
    uint32_t height_;
    int32_t depth_;

private:
    bool inbounds(Position position) const;
    bool inbounds_z(Position position) const;

    MapTile* get_tile_at(Position position);
    MapTile* get_tile_at(uint32_t x, uint32_t y);

    const MapTile* get_tile_at(Position position) const;
    const MapTile* get_tile_at(uint32_t x, uint32_t y) const;

public:
    Map(uint32_t width, uint32_t height, int32_t depth);

    bool passable(uint32_t x, uint32_t y) const;
    bool impassable(uint32_t x, uint32_t y) const;
    int32_t move_cost(uint32_t x, uint32_t y) const;


    const MapTile& at(uint32_t x, uint32_t y) const;
    MapTile& at(uint32_t x, uint32_t y);
    MapTile& at(Position position);
    const MapTile& at(Position position) const;

    void staticjson_init(staticjson::ObjectHandler *h);
};