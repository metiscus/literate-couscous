#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <string>
#include <unordered_map>

class Tileset
{
    sf::Texture texture_;

    sf::Vector2u size_;

    std::unordered_map<uint32_t, sf::IntRect> extents_;
    std::unordered_map<std::string, uint32_t> names_;

public:
    Tileset();

    void load(const std::string& file);


    sf::Vector2u get_size() const;

    inline const sf::Texture& get_texture() const { return texture_; }
    inline sf::Texture& get_texture() { return texture_; }

    sf::IntRect lookup_tile(uint32_t id) const;
    sf::IntRect lookup_tile(std::string name) const;
    uint32_t lookup_tile_index(std::string name) const;
};