#include "window.h"

#define NK_INCLUDE_STANDARD_VARARGS

#include "nuklear.h"
#include "nuklear_sfml_gl2.h"
 
#include <SFML/OpenGL.hpp>

#include "game.h"

#include "ui.h"

namespace ui
{       
    Window::Window(std::string name, sf::FloatRect rect, bool movable, bool resizable, bool closable)
        : name_(name)
        , rect_(rect)
        , flags_(NK_WINDOW_BORDER | NK_WINDOW_TITLE)
        , is_closed_(false)
    {
        // Compute the value for the flags
        if(movable)   flags_ |= NK_WINDOW_MOVABLE;
        if(resizable) flags_ |= NK_WINDOW_SCALABLE;
        if(closable)  flags_ |= NK_WINDOW_CLOSABLE;
    }

    void Window::add_child(ObjectPtr object)
    {
        children_.push_back(object);
    }

    void Window::draw()
    {
        is_closed_ = !nk_begin(ui::get_context(), name_.c_str(), nk_rect(rect_.left, rect_.top, rect_.width, rect_.height), flags_);
        if(!is_closed_)
        {
            for(auto child : children_)
            {
                child->draw();
            }
        }
        nk_end(ui::get_context());
    }
}