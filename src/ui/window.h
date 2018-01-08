#pragma once
#ifndef UI_WINDOW_H_INCLUDED
#define UI_WINDOW_H_INCLUDED

#include "ui/object.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

namespace ui
{
    class Layout;

    class Window : public Object
    {
        std::vector<ObjectPtr> children_;
        std::string name_;
        sf::FloatRect rect_;
        uint32_t flags_;

        bool is_closed_;


    public:
        Window(std::string name, sf::FloatRect rect, bool movable, bool resizable, bool closable);

        void add_child(ObjectPtr object);

        virtual void draw();

        inline bool is_closed() { return is_closed_; }
    };
}

#endif // UI_WINDOW_H_INCLUDED