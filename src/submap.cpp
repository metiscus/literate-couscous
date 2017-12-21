#include "submap.h"

MapTile::MapTile(SubMap* submap, uint32_t x, uint32_t y)
    : submap_(submap)
    , x_(x)
    , y_(y)
{
    ;
}

void MapTile::set_terrain(uint32_t x, uint32_t y, TerrainId id)
{
    if(submap_)
    {
        submap_->terrain_[x][y] = id;
    }
}

TerrainId MapTile::get_terrain(uint32_t x, uint32_t y) const
{
    if(submap_)
    {
        return submap_->terrain_[x][y];
    }
    else
    {
        return TerrainId::Invalid;
    }
}

uint32_t MapTile::get_object_count() const
{
    if(submap_)
    {
        return submap_->objects.size();
    }
    else 
    {
        return 0;
    }
}