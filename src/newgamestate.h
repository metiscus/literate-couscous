#pragma once

#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "race.h"
#include <vector>
#include <string>

class NewGameState : public GameState
{
    sf::View view_;
    char player_name_[256];
    std::vector<Race> races_;
    std::vector<std::string> race_names_;

public:
    NewGameState(Game* game);
    
    virtual ~NewGameState();

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handle_input();
};
