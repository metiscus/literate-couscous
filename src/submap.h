#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class Object;

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

struct SubMap
{
    uint32_t x;
    uint32_t y;

    std::vector<std::unique_ptr<Object>> objects;

    constexpr static uint32_t width = 20;
    constexpr static uint32_t height = 20;
    TerrainId terrain_[width][height];

};

class MapTile
{
    uint32_t x_;
    uint32_t y_;

    SubMap *const submap_;


    friend class Map;
public:
    MapTile(SubMap* submap, uint32_t x, uint32_t y);

    void set_terrain(uint32_t x, uint32_t y, TerrainId id);
    TerrainId get_terrain(uint32_t x, uint32_t y) const;

    uint32_t get_object_count() const;
};