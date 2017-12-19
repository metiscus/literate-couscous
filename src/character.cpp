#include "character.h"

Character::Character(uint32_t id)
    : id_(id)
    , type_(0)
    , name_("(invalid character)")
    , race_id_(0)
{
    ;
}

uint32_t Character::get_id() const
{
    return id_;
}

uint32_t Character::get_type() const
{
    return type_;
}

std::string Character::get_name() const
{
    return name_;
}

uint32_t Character::get_race_id() const
{
    return race_id_;
}

const Attributes& Character::get_attributes() const
{
    return attributes_;
}

Attributes& Character::get_attributes()
{
    return attributes_;
}

void Character::set_type(uint32_t type)
{
    type_ = type;
}

void Character::set_name(const std::string& name)
{
    name_ = name;
}

void Character::set_race_id(uint32_t id)
{
    race_id_ = id;
}

void Character::set_attributes(Attributes atts)
{
    attributes_ = atts;
}

Inventory& Character::get_inventory()
{
    return inventory_;
}

const Inventory& Character::get_inventory() const
{
    return inventory_;
}

void Character::staticjson_init(staticjson::ObjectHandler *h)
{
    h->add_property("id", &id_);
    h->add_property("type", &type_);
    h->add_property("name", &name_);
    h->add_property("race_id", &race_id_);
    h->add_property("attributes", &attributes_);
    h->add_property("inventory", &inventory_);
}