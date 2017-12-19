#include "physicalcomponent.h"

using namespace staticjson;


PhysicalComponent::PhysicalComponent()
    : Component(ComponentType::Physical, "Physical Component")
    , weight_(1)
    , volume_(0.1)
    , value_(1)
{
    ;
}

PhysicalComponent::PhysicalComponent(float weight, float volume, uint32_t value)
    : Component(ComponentType::Physical, "Physical Component")
    , weight_(weight)
    , volume_(volume)
    , value_(value)
{
    ;
}

float PhysicalComponent::get_weight() const
{
    return weight_;
}

float PhysicalComponent::get_volume() const
{
    return volume_;
}

uint32_t PhysicalComponent::get_value() const
{
    return value_;
}

void PhysicalComponent::staticjson_init(ObjectHandler *h)
{
    h->add_property("type", &type_);
    h->add_property("name", &name_);
    h->add_property("weight", &weight_);
    h->add_property("volume", &volume_);
    h->add_property("value", &value_);
}