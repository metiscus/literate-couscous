#include "mainmenustate.h"
#include "game.h"

#include "newgamestate.h"

#include "ui/ui.h"

MainMenuState::MainMenuState(Game* game)
    : GameState(game)
{
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::draw(const float dt)
{
    assert(get_window());
    get_window()->setView(view_);
    get_window()->clear(sf::Color::Black);
    
    struct nk_color background;
    background = nk_rgb(28,48,62);    
    
    static float value = 0.6f;
    static int i =  20;

    bool do_newgame = false;
    bool do_exit = false;

    if (nk_begin(ui::get_context(), "Main Menu", nk_rect(50, 50, 220, 220),
    NK_WINDOW_BORDER|NK_WINDOW_TITLE)) 
    {
        /* fixed widget pixel width */
        nk_layout_row_dynamic(ui::get_context(), 30, 2);
        if (nk_button_label(ui::get_context(), "New Game")) {
            //get_game()->change_state(std::make_shared<NewGameState>(get_game()));
            do_newgame = true;
        }
        
        nk_layout_row_dynamic(ui::get_context(), 30, 2);
        if (nk_button_label(ui::get_context(), "Continue")) {
            //todo transition to next
        }

        nk_layout_row_dynamic(ui::get_context(), 30, 2);
        if (nk_button_label(ui::get_context(), "Exit")) {
            do_exit = true;
        }
    }
    nk_end(ui::get_context());
    
    
    // Actually handle the drawing here
    /* Draw */
    float bg[4];
    get_window()->setActive(true);
    nk_color_fv(bg, background);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg[0], bg[1], bg[2], bg[3]);
    /* IMPORTANT: `nk_sfml_render` modifies some global OpenGL state
    * with blending, scissor, face culling and depth test and defaults everything
    * back into a default state. Make sure to either save and restore or
    * reset your own state after drawing rendering the UI. */
    nk_sfml_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

    if(do_newgame)
    {
        //get_game()->change_state(std::make_shared<NewGameState>(get_game()));
        get_game()->push_state(std::make_shared<NewGameState>(get_game()));
    }

    if(do_exit)
    {
        get_window()->close();
    }
}

void MainMenuState::update(const float dt)
{
    // nothing here
}

void MainMenuState::handle_input()
{
    // Process events
    sf::Event event;
    
    ui::begin_event_processing();
    while(get_window()->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            get_window()->close();
        }
        else if(event.type == sf::Event::Resized)
        {
            glViewport(0, 0, event.size.width, event.size.height);
        }
        ui::process_event(event);
    }
    
    ui::end_event_processing();
}
