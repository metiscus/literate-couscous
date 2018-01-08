#include "ui.h"

#include "nuklear.h"
#include "nuklear_sfml_gl2.h"

//#include <SFML/OpenGL.hpp>
#include <cassert>

namespace ui
{
    namespace 
    {
        nk_context    *nk_context_ = nullptr;
        nk_font_atlas *nk_atlas_   = nullptr;
        std::shared_ptr<sf::RenderWindow> window_;
    }

    void initialize(std::shared_ptr<sf::RenderWindow> window)
    {
        assert(window);
        window_ = window;

        nk_context_ = nk_sfml_init(window_.get());
        assert(nk_context_);
    
        // Build a font atlas
        struct nk_font_atlas *atlas;
        nk_sfml_font_stash_begin(&atlas);
        nk_sfml_font_stash_end();
    }


    void shutdown()
    {
        if(nk_context_)
        {
            nk_sfml_shutdown();
        }
        window_.reset();
    }


    void begin_event_processing()
    {
        nk_input_begin(nk_context_);
    }

    void process_event(sf::Event event)
    {
        nk_sfml_handle_event(&event);
    }

    void end_event_processing()
    {
        nk_input_end(nk_context_);
    }

    nk_context* get_context()
    {
        return nk_context_;
    }
}
