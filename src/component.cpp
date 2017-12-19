#include "component.h"

Component::Component(Type type, std::string name)
    : type_(type)
    , name_(name)
{
    ;
}

Component::Type Component::get_type() const
{
    return type_;
}

std::string Component::get_name() const
{
    return name_;
}