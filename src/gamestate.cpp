#include "gamestate.h"
#include "game.h"

GameState::GameState(Game* game)
    : game_(game)
{ 
    assert(game_);
    window_ = game_->get_window();
}


std::shared_ptr<sf::RenderWindow> GameState::get_window() { return window_; }
