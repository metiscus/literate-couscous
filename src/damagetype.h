#pragma once

#include <staticjson/staticjson.hpp>

struct Damage
{
    enum class Type
    {
        Invalid,
        Blunt,
        Pierce,
        Ballistic,
        Radiation,
        Thermal,
    };

    Type type;
    int amount;

    void staticjson_init(staticjson::ObjectHandler *h)
    {
        h->add_property("type", &type);
        h->add_property("amount", &amount);
    }
};


STATICJSON_DECLARE_ENUM(Damage::Type,
    {"Invalid", Damage::Type::Invalid},
    {"Blunt", Damage::Type::Blunt},
    {"Pierce", Damage::Type::Pierce},
    {"Ballistic", Damage::Type::Ballistic},
    {"Radiation", Damage::Type::Radiation},
    {"Thermal", Damage::Type::Thermal},
)

