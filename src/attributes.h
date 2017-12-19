#pragma once

#include <staticjson/staticjson.hpp>

struct Attribute
{
    int base;
    int modifier;

    Attribute()
        : base(5), modifier(0)
    {}

    inline void reset()
    {
        modifier = 0;
    }

    inline void staticjson_init(staticjson::ObjectHandler *h)
    {
        h->add_property("base", &base);
        h->add_property("modifier", &modifier);
    }
};

struct Attributes
{
    Attribute strength;
    Attribute agility;
    Attribute intelligence;

    inline void staticjson_init(staticjson::ObjectHandler *h)
    {
        h->add_property("strength", &strength);
        h->add_property("agility", &agility);
        h->add_property("intelligence", &intelligence);
    }
};