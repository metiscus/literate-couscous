#include "mapgen.h"

#include "map.h"
#include <random>

Mapgen::Mapgen(uint32_t width, uint32_t height, int32_t depth)
    : width_(width)
    , height_(height)
    , depth_(depth)
{
    ;
}

std::shared_ptr<Map> Mapgen::generate_outdoors_map(uint32_t seed)
{
    auto map = std::make_shared<Map>(width_, height_, depth_);

    for(uint32_t yy=0; yy<height_; ++yy)
    {
        for(uint32_t xx=0; xx<width_; ++xx)
        {
            auto& tile = map->at(xx,yy);
            tile.set_terrain(TerrainId::Outdoor_Grass);
        }
    }

    return map;
}