#include "game.h"

#include "newgamestate.h"
#include <iostream>

#include "ui/ui.h"

NewGameState::NewGameState(Game* game)
    : GameState(game)
{
    strcpy(player_name_, "Jakob Strussel");

    if(game)
    {
        races_ = game->get_races();
        for(auto race : races_)
        {
            race_names_.push_back(race.get_name());
        }
    }
}

NewGameState::~NewGameState()
{

}

void NewGameState::draw(const float dt)
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

    if (nk_begin(ui::get_context(), "Create your Character", nk_rect(50, 50, 500, 400),
    NK_WINDOW_BORDER|NK_WINDOW_TITLE)) 
    {
        /* fixed widget pixel width */
        //nk_layout_row_static(ui::get_context(), 30, 80, 1);
        /*
        if (nk_button_label(ui::get_context(), "New Game")) {
            //get_game()->change_state(std::make_shared<InGameState>(get_game()));
        }
        */
        nk_layout_row_dynamic(ui::get_context(), 30, 2);
        nk_label(ui::get_context(), "Character Name: ", NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ui::get_context(), NK_EDIT_FIELD|NK_TEXT_EDIT_SINGLE_LINE, player_name_, sizeof(player_name_), nk_filter_ascii);
        static std::string old = player_name_;
        std::string ns = player_name_;
        if(ns != old)
        {
            std::cerr<<"New: "<<ns<<"\n";
            old = ns;
        }
        
        // Race select
        std::vector<const char*> race_name_list;
        for(auto name : race_names_)
        {
            race_name_list.push_back(&name[0]);
        }

        nk_layout_row_dynamic(ui::get_context(), 30, 2);
        nk_label(ui::get_context(), "Race: ", NK_TEXT_LEFT);
        static int race_selected = 0;
        struct nk_vec2 size = {100, 50};
        nk_combobox(ui::get_context(), &race_name_list[0], race_name_list.size(), &race_selected, 20, size);

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
    nk_sfml_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void NewGameState::update(const float dt)
{
    // nothing here
}

void NewGameState::handle_input()
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
