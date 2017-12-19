#include "object.h"
#include "physicalcomponent.h"

#include <staticjson/optional_support.hpp>

using namespace staticjson;

Object::Object(uint32_t id, uint32_t type, std::string name)
    : id_(id)
    , type_(type)
    , name_(name)
    , is_stackable_(false)
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

bool  Object::get_is_stackable() const
{
    return is_stackable_;
}

PhysicalComponent* Object::get_physical_component()
{
    if(physical_.has_value())
        return physical_.value().get();
    else
        return nullptr;
}

void Object::set_physical_component(std::unique_ptr<PhysicalComponent> component)
{
    physical_ = std::move(component);
}

void Object::set_is_stackable(bool value)
{
    is_stackable_ = value;
}

std::unique_ptr<Object> Object::clone() const
{
    auto obj = std::make_unique<Object>(id_, type_, name_);

    if(physical_.has_value())
    {
        obj->physical_ = physical_.value()->clone();
    }

    return obj;
}

void Object::staticjson_init(ObjectHandler *h)
{
    h->add_property("id", &id_);
    h->add_property("type", &type_);
    h->add_property("name", &name_);
    h->add_property("is_stackable", &is_stackable_);
    h->add_property("physical", &physical_, Flags::Optional);
}
