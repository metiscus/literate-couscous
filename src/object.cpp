#include "object.h"

Object::Object(uint32_t id, uint32_t type, std::string name)
    : id_(id)
    , type_(type)
    , name_(name)
{
    ;
}

uint32_t Object::get_id() const
{
    return id_;
}

uint32_t Object::get_type() const
{
    return type_;
}

std::string Object::get_name() const
{
    return name_;
}