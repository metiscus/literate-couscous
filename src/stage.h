#pragma once
#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include "drawable.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

class Stage
{
private:
    std::vector<DrawablePtr> drawables_;
    sf::View view_;
    
    sf::Vector2f center_;
    sf::Vector2f size_;

public:
    Stage();
    Stage(const Stage&) = delete;
    Stage& operator=(Stage&) = delete;
    
    virtual ~Stage() = default;

    void set_view(sf::View view);
    void set_view(sf::FloatRect rect);
    void set_viewport(sf::FloatRect rect);

    inline sf::View get_view() const { return view_; }
    inline sf::FloatRect get_viewport() const { return view_.getViewport(); }
    
    void zoom(float zoom);
    void set_center(sf::Vector2f center);
    void set_size(sf::Vector2f size);
    void move(sf::Vector2f distance);

    inline sf::Vector2f get_center() { return view_.getCenter(); }
    inline sf::Vector2f get_size() { return view_.getSize(); }

    void add(DrawablePtr drawable);
    void remove(DrawablePtr drawable);
    void draw(std::shared_ptr<sf::RenderWindow> window);
};


#endif
