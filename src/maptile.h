#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <staticjson/staticjson.hpp>

#include "object.h"

enum class TerrainId
{
    Invalid,
    Outdoor_Grass,
    Outdoor_Dirt,
    Outdoor_Water,
    Outdoor_Asphalt,
    Outdoor_Wall,
    Outdoor_Door,
    Indoor_Floor,
    Indoor_Wall,
    Indoor_Door,
};


STATICJSON_DECLARE_ENUM(TerrainId,
    {"Invalid", TerrainId::Invalid},
    {"Outdoor_Grass", TerrainId::Outdoor_Grass},
    {"Outdoor_Dirt", TerrainId::Outdoor_Dirt},
    {"Outdoor_Water", TerrainId::Outdoor_Water},
    {"Outdoor_Asphalt", TerrainId::Outdoor_Asphalt},
    {"Outdoor_Wall", TerrainId::Outdoor_Wall},
    {"Outdoor_Door", TerrainId::Outdoor_Door},
    {"Indoor_Floor", TerrainId::Indoor_Floor},
    {"Indoor_Wall", TerrainId::Indoor_Wall},
    {"Indoor_Door", TerrainId::Indoor_Door},
)

class MapTile
{
    TerrainId terrain_;
    std::vector<std::unique_ptr<Object>> objects_;

    friend class Map;
public:
    MapTile();

    void set_terrain(TerrainId id);
    TerrainId get_terrain() const;

    uint32_t get_object_count() const;

    void staticjson_init(staticjson::ObjectHandler *h);
};
