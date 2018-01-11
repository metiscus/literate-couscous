#pragma once

#ifndef INGAMESTATE_H_INCLUDED
#define INGAMESTATE_H_INCLUDED

#include "drawable.h"
#include "gamestate.h"
#include "stage.h"

enum class ActionState { NONE, PANNING };

class Map;

class InGameState : public GameState
{
    Stage stage_;

    ActionState action_state_;
    
    std::shared_ptr<Map> map_;

    sf::Vector2i panning_anchor_;
    float zoom_level_;

    sf::Vector2f player_location_;

public:
    InGameState(Game* game);
    
    virtual ~InGameState() = default;

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handle_input();
};

#endif
