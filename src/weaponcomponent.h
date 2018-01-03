#pragma once

#include <cstdint>

#include "component.h"
#include <staticjson/staticjson.hpp>

enum class WeaponType
{
    Invalid,
    Melee,
    Throwable,
    Gun
};

STATICJSON_DECLARE_ENUM(WeaponType,
    {"Invalid", WeaponType::Invalid},
    {"Melee", WeaponType::Melee},
    {"Throwable", WeaponType::Throwable},
    {"Gun", WeaponType::Gun},
)

class WeaponComponent 
    : public Component<WeaponComponent>
{
    WeaponType type_;
    uint32_t ammo_capacity_;
    uint32_t max_range_;
    uint32_t min_range_;

public:
    WeaponComponent()
        : Component(ComponentType::Weapon, "Weapon Component")
        , ammo_capacity_(0)
        , max_range_(0)
        , min_range_(0)
    {

    }

    inline WeaponType get_type() const { return type_; }
    inline uint32_t get_ammo_capacity() const { return ammo_capacity_; }
    inline uint32_t get_max_range() const { return max_range_; }
    inline uint32_t get_min_range() const { return min_range_; }

    inline void set_type(WeaponType type) { type_ = type; }
    inline void set_ammo_capacity(uint32_t capacity) { ammo_capacity_ = capacity; }
    inline void set_max_range(uint32_t max_range) { max_range_ = max_range; }
    inline void set_min_range(uint32_t min_range) { min_range_ = min_range; }

    std::unique_ptr<WeaponComponent> clone() const
    {
        return std::make_unique<WeaponComponent>(*this);
    }

    inline void staticjson_init(staticjson::ObjectHandler *h)
    {
        h->add_property("type", &type_);
        h->add_property("ammo_capacity", &ammo_capacity_);
        h->add_property("max_range", &max_range_);
        h->add_property("min_range", &min_range_);
    }
};
