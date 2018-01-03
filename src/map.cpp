#include "map.h"
#include "maptile.h"
#include "object.h"

Map::Map(int32_t width, int32_t height, int32_t depth)
    : width_(width)
    , height_(height)
    , depth_(depth)
{
    tiles_.resize(width*height*depth);
}

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

MapTile* Map::get_tile_at(Position position)
{
    if(!inbounds_z(position))
    {
        return nullptr;
    }

    uint32_t index = position.z + position.x * (width_ * depth_) + position.y * depth_;
    return &tiles_[index];
}

MapTile* Map::get_tile_at(int32_t x, int32_t y)
{
    if(!inbounds(Position(x, y, 0)))
    {
        return nullptr;
    }

    uint32_t index = x * (width_ * depth_) + y * depth_;
    return &tiles_[index];
}

const MapTile* Map::get_tile_at(Position position) const
{
    if(!inbounds_z(position))
    {
        return nullptr;
    }

    uint32_t index = position.z + position.x * (width_ * depth_) + position.y * depth_;
    return &tiles_[index];
}

const MapTile* Map::get_tile_at(int32_t x, int32_t y) const
{
    if(!inbounds(Position(x, y, 0)))
    {
        return nullptr;
    }

    uint32_t index = x * (width_ * depth_) + y * depth_;
    return &tiles_[index];
}

bool Map::passable(int32_t x, int32_t y) const
{
    const MapTile* sm = get_tile_at(x, y);
    if(!sm)
    {
        return false;
    }

    switch(sm->get_terrain())
    {
        case TerrainId::Outdoor_Grass:
        case TerrainId::Outdoor_Dirt:
        case TerrainId::Outdoor_Asphalt:
        case TerrainId::Outdoor_Door:
        case TerrainId::Indoor_Floor:
        case TerrainId::Indoor_Door:
            return true;
            break;
    
        case TerrainId::Outdoor_Wall:
        case TerrainId::Outdoor_Water:
        case TerrainId::Indoor_Wall:
        case TerrainId::Invalid:
        default:
            return true;
            break;
    }
}

bool Map::impassable(int32_t x, int32_t y) const
{
    return !passable(x, y);
}

int32_t Map::move_cost(int32_t x, int32_t y) const
{

}

const MapTile& Map::at(int32_t x, int32_t y) const
{
    assert(inbounds(Position(x, y, 1)));

    uint32_t index = 1 + x * (width_ * depth_) + y * depth_;
    return tiles_[index];
}

MapTile& Map::at(int32_t x, int32_t y)
{
    assert(inbounds(Position(x, y, 1)));

    uint32_t index = 1 + x * (width_ * depth_) + y * depth_;
    return tiles_[index];
}

MapTile& Map::at(Position position)
{
    assert(inbounds(position));

    uint32_t index = position.z + position.x * (width_ * depth_) + position.y * depth_;
    return tiles_[index];
}

const MapTile& Map::at(Position position) const
{
    assert(inbounds(position));

    uint32_t index = position.z + position.x * (width_ * depth_) + position.y * depth_;
    return tiles_[index];
}

void Map::staticjson_init(staticjson::ObjectHandler *h)
{
    h->add_property("tiles", &tiles_);
    h->add_property("width", &width_);
    h->add_property("height", &height_);
    h->add_property("depth", &depth_);
}