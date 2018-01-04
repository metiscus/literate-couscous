#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <staticjson/staticjson.hpp>
#include <string>
#include <unordered_map>

#include "hascomponent.h"
#include "physicalcomponent.h"
#include "weaponcomponent.h"
#include "wearablecomponent.h"


class Object;
typedef std::unique_ptr<Object> ObjectPtr;

class Object
{
    uint32_t id_;
    uint32_t type_;
    std::string name_;

    HasComponent<PhysicalComponent> physical_;
    HasComponent<WeaponComponent> weapon_;
    HasComponent<WearableComponent> wearable_;

    bool is_stackable_;
    std::optional<uint32_t> quantity_;

public:
    Object(uint32_t id = 0, uint32_t type = 0, std::string name = "");

    uint32_t get_id() const;
    uint32_t get_type() const;
    std::string get_name() const;
    bool get_is_stackable() const;
    uint32_t get_quantity() const;

    PhysicalComponent* get_physical_component()
    {
        return physical_.value();
    }

    const PhysicalComponent* get_physical_component() const
    {
        return physical_.value();
    }

    void set_physical_component(std::unique_ptr<PhysicalComponent> component)
    {
        physical_.set_value(std::move(component));
    }

    WeaponComponent* get_weapon_component()
    {
        return weapon_.value();
    }

    const WeaponComponent* get_weapon_component() const
    {
        return weapon_.value();
    }

    void set_weapon_component(std::unique_ptr<WeaponComponent> component)
    {
        weapon_.set_value(std::move(component));
    }

    WearableComponent* get_wearable_component()
    {
        return wearable_.value();
    }

    const WearableComponent* get_wearable_component() const
    {
        return wearable_.value();
    }

    void set_wearable_component(std::unique_ptr<WearableComponent> component)
    {
        wearable_.set_value(std::move(component));
    }


    void set_is_stackable(bool value);
    void change_quantity(int32_t value);
    void set_quantity(uint32_t value);

    ObjectPtr clone() const;

    void staticjson_init(staticjson::ObjectHandler *h);

    //bool operator=(const Object& rhs) const;
};