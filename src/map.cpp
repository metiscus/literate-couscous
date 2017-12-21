#include "map.h"
#include "submap.h"

bool Map::inbounds(Position position) const
{
    if((position.x < 0)       ||
       (position.x >= width_) ||
       (position.y < 0)       ||
       (position.y >= height_)  )
    {
        return false;
    }

    return true;
}

bool Map::inbounds_z(Position position) const
{
    if(position.z >= depth_)
    {
        return false;
    }

    return true;
}

SubMap* Map::get_submap_at(Position position)
{
    if(!inbounds_z(position))
    {
        return nullptr;
    }

    uint32_t index = position.z + position.x * (width_ * depth_) + position.y * depth_;
    return tiles_[index].submap_;
}

SubMap* Map::get_submap_at(int32_t x, int32_t y)
{
    if(!inbounds(Position(x, y, 0)))
    {
        return nullptr;
    }

    uint32_t index = x * (width_ * depth_) + y * depth_;
    return tiles_[index].submap_;
}