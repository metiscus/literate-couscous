#pragma once
#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include <cstdint>
#include <memory>
#include <SFML/Graphics.hpp>

class Drawable
{
    int32_t layer_;

public:
    Drawable(int32_t layer = 0) : layer_(layer) { }
    
    virtual ~Drawable() = default;
    
    inline void set_layer(int32_t layer) { layer_ = layer; }
    inline int32_t get_layer() const { return layer_; }

    virtual void draw(std::shared_ptr<sf::RenderWindow>) = 0;
};

typedef std::shared_ptr<Drawable> DrawablePtr;

#endif
