#pragma once

class Game;

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

class GameState
{
    Game* game_;
    std::shared_ptr<sf::RenderWindow> window_;

protected:
    std::shared_ptr<sf::RenderWindow> get_window();

public:
    GameState(Game* game = nullptr);

    virtual ~GameState() = default;
    
    inline void set_game(Game* game) { game_ = game; }
    inline Game* get_game() { return game_; }
    
    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handle_input() = 0;
};

typedef std::shared_ptr<GameState> GameStatePtr;
