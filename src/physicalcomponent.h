#pragma once

#include <cstdint>

#include "component.h"

class PhysicalComponent 
    : public Component<PhysicalComponent>
{
    float weight_;
    float volume_;
    uint32_t value_;

public:
    PhysicalComponent();
    PhysicalComponent(float weight, float volume, uint32_t value);

    float get_weight() const;
    float get_volume() const;
    uint32_t get_value() const;

    void staticjson_init(staticjson::ObjectHandler *h);
};