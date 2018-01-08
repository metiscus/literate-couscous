#pragma once
#ifndef UI_LAYOUT_H_INCLUDED
#define UI_LAYOUT_H_INCLUDED

#include "global.h"

#include "object.h"

namespace ui
{
    class Layout : public Object
    {
    public:
        Layout() = default;

        virtual void draw();
    };
}

#endif // UI_LAYOUT_H_INCLUDED