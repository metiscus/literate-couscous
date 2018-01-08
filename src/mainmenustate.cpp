#include "mainmenustate.h"
#include "game.h"

//#include "ingamestate.h"

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
    
    // draw some ui stuff here
    enum {EASY, HARD};
    static int op = EASY;
    static float value = 0.6f;
    static int i =  20;

    if (nk_begin(ui::get_context(), "Main Menu", nk_rect(50, 50, 220, 220),
    NK_WINDOW_BORDER|NK_WINDOW_TITLE)) 
    {
        /* fixed widget pixel width */
        nk_layout_row_static(ui::get_context(), 30, 80, 1);
        if (nk_button_label(ui::get_context(), "New Game")) {
            //get_game()->change_state(std::make_shared<InGameState>(get_game()));
        }
        
        /* fixed widget pixel width */
        nk_layout_row_static(ui::get_context(), 30, 80, 1);
        if (nk_button_label(ui::get_context(), "Continue")) {
            //todo transition to next
        }
        
        /* fixed widget pixel width */
        nk_layout_row_static(ui::get_context(), 30, 80, 1);
        if (nk_button_label(ui::get_context(), "Exit")) {
            get_window()->close();
        }

        /* fixed widget window ratio width */
        nk_layout_row_dynamic(ui::get_context(), 30, 2);
        if (nk_option_label(ui::get_context(), "easy", op == EASY)) op = EASY;
        if (nk_option_label(ui::get_context(), "hard", op == HARD)) op = HARD;

        /* custom widget pixel width */
        nk_layout_row_begin(ui::get_context(), NK_STATIC, 30, 2);
        {
            nk_layout_row_push(ui::get_context(), 50);
            nk_label(ui::get_context(), "Volume:", NK_TEXT_LEFT);
            nk_layout_row_push(ui::get_context(), 110);
            nk_slider_float(ui::get_context(), 0, &value, 1.0f, 0.1f);
        }
        nk_layout_row_end(ui::get_context());
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
    nk_sfml_render(NK_ANTI_ALIASING_ON);
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
