#pragma once
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <memory>
#include <SFML/System.hpp>
#include "drawable.h"

//TODO: remove this once we are using the new wrappers
#define NK_INCLUDE_STANDARD_VARARGS

#include "nuklear.h"
#include "nuklear_sfml_gl2.h"
 
#include <SFML/OpenGL.hpp>

namespace ui
{
    void initialize(std::shared_ptr<sf::RenderWindow> window);

    void begin_event_processing();

    void process_event(sf::Event event);

    void end_event_processing();

    void shutdown();

    nk_context* get_context();
}

#endif // UI_H_INCLUDED

