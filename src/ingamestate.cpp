#include <cmath>
#include "ingamestate.h"
#include "game.h"
#include "map.h"
#include "ui/ui.h"
#include "ui/window.h"


InGameState::InGameState(Game* game)
    : GameState(game)
    , action_state_(ActionState::NONE)
    , zoom_level_(1.0f)
    , player_location_(0, 0)
{
    //level_ = std::make_shared<Level>();

    sf::FloatRect view = sf::FloatRect(0, 768, 1024, 768);
    auto cache = get_game()->get_cache();

    stage_.add(cache->world->get_current_map());
}

void InGameState::draw(const float dt)
{
    (void)dt;
    get_window()->clear(sf::Color::Black);

    // Clear the window to prepare to draw
    //get_window()->clear(sf::Color::Black);
    stage_.draw(get_window());
    
    // Display what has been drawn
    get_window()->display();
}

void InGameState::update(const float dt)
{
    // do nothing here
    (void)dt;
}

void InGameState::handle_input()
{
    ui::begin_event_processing();

    // Process events
    sf::Event event;
    while(get_window()->pollEvent(event))
    {
        ui::process_event(event);

        switch(event.type)
        {
            case sf::Event::Closed:
            {
                get_window()->close();
                break;
            }
        
            case sf::Event::Resized:
            {
                stage_.set_size(sf::Vector2f(event.size.width, event.size.height));
                //stage_.zoom(zoom_level_);
                break;
            }
        
            case sf::Event::MouseMoved:
            {
                if(action_state_ == ActionState::PANNING)
                {
                    // Pan the camera around
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*get_window()) - panning_anchor_);
                    stage_.move(-1.0f * pos * zoom_level_);
                    panning_anchor_ = sf::Mouse::getPosition(*get_window());
                }

                break;
            }
            
            case sf::Event::MouseButtonPressed:
            {
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    // If we are not already panning
                    if(action_state_ != ActionState::PANNING)
                    {
                        action_state_ = ActionState::PANNING;
                        panning_anchor_ = sf::Mouse::getPosition(*get_window());
                    }
                }

                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    // Convert the mouse position into normalized coordinates
                    sf::Vector2f window_size  = sf::Vector2f (Game::get()->get_window_size());
                    sf::Vector2f mouse_window = sf::Vector2f(sf::Mouse::getPosition(*get_window()));
                    //TODO: check for 0 here
                    mouse_window.x /= window_size.x;
                    mouse_window.y /= window_size.y;
                    mouse_window -= sf::Vector2f(0.5, 0.5);

                    // transform the normalized coordinates into world coordinates
                    //stage_.get_center().y, stage_.get_size().x, stage_.get_size().y);
                    sf::Vector2f view_center = stage_.get_center();
                    sf::Vector2f view_size   = stage_.get_size();
                    sf::Vector2f mouse_world = sf::Vector2f(mouse_window.x * view_size.x, mouse_window.y * view_size.y);
                    mouse_world += view_center;

                    //map_->set_player_position(sf::Vector2u(mouse_world));

                    player_location_ = mouse_world;
                }


                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    // Convert the mouse position into normalized coordinates
                    sf::Vector2f window_size  = sf::Vector2f (Game::get()->get_window_size());
                    sf::Vector2f mouse_window = sf::Vector2f(sf::Mouse::getPosition(*get_window()));
                    //TODO: check for 0 here
                    mouse_window.x /= window_size.x;
                    mouse_window.y /= window_size.y;
                    mouse_window -= sf::Vector2f(0.5, 0.5);

                    // transform the normalized coordinates into world coordinates
                    //stage_.get_center().y, stage_.get_size().x, stage_.get_size().y);
                    sf::Vector2f view_center = stage_.get_center();
                    sf::Vector2f view_size   = stage_.get_size();
                    sf::Vector2f mouse_world = sf::Vector2f(mouse_window.x * view_size.x, mouse_window.y * view_size.y);
                    mouse_world += view_center;

                    // Determine angle to heading
                    sf::Vector2f toCursor = mouse_world - player_location_;
                    toCursor /= (float)(sqrtf(powf(toCursor.x, 2.0f) + powf(toCursor.y, 2.0f)) + 0.01);
                    
                    float heading = 90.0 + atan2(toCursor.y, toCursor.x) * 180.0 / 3.14159;
                    //map_->set_player_orientation(heading);
                    //map_->set_player_position(sf::Vector2u(mouse_world));
                }
                
                break;
            }
            
            case sf::Event::MouseButtonReleased:
            {
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    action_state_ = ActionState::NONE;
                }

                break;
            }
            
            case sf::Event::MouseWheelMoved:
            {
                if(event.mouseWheel.delta < 0)
                {
                    stage_.zoom(1.2f);
                    zoom_level_ *= 1.2f;
                }
                else
                {
                    stage_.zoom(0.8f);
                    zoom_level_ *= 0.8f;
                }
                break;
            }
            
            default:
                break;
        }
    }
    
    ui::end_event_processing();
}
