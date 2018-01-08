#pragma once

#include <SFML/Graphics.hpp>
#include "gamestate.h"

class MainMenuState : public GameState
{
    sf::View view_;
    
public:
    MainMenuState(Game* game);
    
    virtual ~MainMenuState();

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handle_input();
};
