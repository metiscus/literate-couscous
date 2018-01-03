#include "maptile.h"
#include "object.h"

MapTile::MapTile()
    : terrain_(TerrainId::Invalid)
{
    ;
}

void MapTile::set_terrain(TerrainId id)
{
    terrain_ = id;
}

TerrainId MapTile::get_terrain() const
{
    return terrain_;
}

uint32_t MapTile::get_object_count() const
{
    return objects_.size();
}

void MapTile::staticjson_init(staticjson::ObjectHandler *h)
{
    h->add_property("terrain", &terrain_);
    h->add_property("objects", &objects_);
}