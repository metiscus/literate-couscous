#pragma once

#include <cstdint>
#include <staticjson/staticjson.hpp>
#include <string>

enum class ComponentType
{
    Physical
};

template <typename T>
class Component
{
protected:
    ComponentType type_;
    std::string name_;

protected:
    Component(ComponentType type, std::string name)
        : type_(type), name_(name)
    {
        ;
    }

public:
    ComponentType get_type() const { return type_; }
    std::string get_name() const { return name_; }
};

STATICJSON_DECLARE_ENUM(ComponentType,
    {"Physical", ComponentType::Physical}
)