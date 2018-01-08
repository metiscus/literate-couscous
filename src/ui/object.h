#pragma once
#ifndef UI_OBJECT_H_INCLUDED
#define UI_OBJECT_H_INCLUDED

#include <memory>

namespace ui
{
    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;

        virtual void draw() = 0;
    };

    typedef std::shared_ptr<Object> ObjectPtr;
}

#endif // UI_OBJECT_H_INCLUDED