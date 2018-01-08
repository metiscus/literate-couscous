#pragma once

#include <SFML/Graphics.hpp>
#include "gamestate.h"

class NewGameState : public GameState
{
    sf::View view_;
    char player_name_[256];

public:
    NewGameState(Game* game);
    
    virtual ~NewGameState();

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handle_input();
};
