#pragma once

#include <cstdint>

#include <staticjson/staticjson.hpp>

struct Position
{
    int32_t x;
    int32_t y;
    int32_t z;

    Position(int32_t x_ = 0, int32_t y_ = 0, int32_t z_ = 0)
        : x(x_), y(y_), z(z_)
    {}

    Position(const Position&) = default;
    Position(Position&&) = default;

    ~Position() = default;

    inline Position operator+(Position rhs) const
    {
        return Position(x+rhs.x, y+rhs.y, z+rhs.z);
    }

    inline Position operator-(Position rhs) const
    {
        return Position(x-rhs.x, y-rhs.y, z-rhs.z);
    }

    inline void operator+=(Position rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
    }

    inline void operator-=(Position rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
    }

    inline void set(int32_t x_, int32_t y_, int32_t z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }

    void staticjson_init(staticjson::ObjectHandler *h)
    {
        h->add_property("x", &x);
        h->add_property("y", &y);
        h->add_property("z", &z);
    }
};