#pragma once

#include <cstdint>
#include "position.h"
#include <vector>
#include "maptile.h"
#include <staticjson/staticjson.hpp>

class Map
{
    std::vector<MapTile> tiles_;
    int32_t width_;
    int32_t height_;
    int32_t depth_;

private:
    bool inbounds(Position position) const;
    bool inbounds_z(Position position) const;

    MapTile* get_tile_at(Position position);
    MapTile* get_tile_at(int32_t x, int32_t y);

    const MapTile* get_tile_at(Position position) const;
    const MapTile* get_tile_at(int32_t x, int32_t y) const;

public:
    Map(int32_t width, int32_t height, int32_t depth);

    bool passable(int32_t x, int32_t y) const;
    bool impassable(int32_t x, int32_t y) const;
    int32_t move_cost(int32_t x, int32_t y) const;


    MapTile& maptile_at(Position position);
    const MapTile& maptile_at(Position position) const;

    void staticjson_init(staticjson::ObjectHandler *h);
};