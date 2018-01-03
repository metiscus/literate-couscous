#include "object.h"
#include "physicalcomponent.h"
#include <cassert>
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

uint32_t Object::get_quantity() const
{
    if(is_stackable_) return quantity_.value();
    return 1;
}

void Object::set_is_stackable(bool value)
{
    is_stackable_ = value;
    if(value == true)
    {
        quantity_ = 1;
    }
    else
    {
        quantity_ = std::nullopt;
    }
}

void Object::change_quantity(int32_t value)
{
    assert(is_stackable_);
    assert(quantity_.has_value());
    assert(uint32_t(value) < quantity_);
    if(quantity_.has_value())
    {
        quantity_ = quantity_.value() + value;
    }
}

void Object::set_quantity(uint32_t value)
{
    assert(is_stackable_);
    assert(quantity_.has_value());
    assert(value != 0);
    if(quantity_.has_value())
    {
        quantity_ = value;
    }
}

std::unique_ptr<Object> Object::clone() const
{
    auto obj = std::make_unique<Object>(id_, type_, name_);

    if(physical_.has_value())
    {
        obj->physical_ = physical_.clone();
    }

    return obj;
}

void Object::staticjson_init(ObjectHandler *h)
{
    h->add_property("id", &id_);
    h->add_property("type", &type_);
    h->add_property("name", &name_);
    h->add_property("is_stackable", &is_stackable_);
    h->add_property("quantity", &quantity_, Flags::Optional);
    h->add_property("physical", &physical_);
    h->add_property("weapon", &weapon_);
}

#if 0
bool Object::operator=(const Object& rhs) const
{
    //This may be tricky later...
    return rhs.type_ == type_;
}
#endif