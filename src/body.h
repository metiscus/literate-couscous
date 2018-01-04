#pragma once

#include <staticjson/staticjson.hpp>

enum class LimbType
{
    Invalid,
    Head,
    Arms,
    Torso,
    Legs,
};

STATICJSON_DECLARE_ENUM(LimbType,
    {"Invalid", LimbType::Invalid},
    {"Head", LimbType::Head},
    {"Arms", LimbType::Arms},
    {"Torso", LimbType::Torso},
    {"Legs", LimbType::Legs},
)