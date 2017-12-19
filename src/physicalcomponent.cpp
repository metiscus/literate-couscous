#include "physicalcomponent.h"

PhysicalComponent::PhysicalComponent(float weight, float volume, uint32_t value)
	: Component(Component::Physical, "Physical Component")
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