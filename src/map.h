#pragma once

#include <cstdint>
#include "position.h"
#include <vector>
#include "submap.h"


class Map
{
    std::vector<MapTile> tiles_;
    int32_t width_;
    int32_t height_;
    int32_t depth_;

private:
    bool inbounds(Position position) const;
    bool inbounds_z(Position position) const;

    SubMap* get_submap_at(Position position);
    SubMap* get_submap_at(int32_t x, int32_t y);

public:
    bool passable(int32_t x, int32_t y) const;
    bool impassable(int32_t x, int32_t y) const;
    int32_t move_cost(int32_t x, int32_t y) const;


    MapTile& maptile_at(Position position);
    const MapTile& maptile_at(Position position) const;
};