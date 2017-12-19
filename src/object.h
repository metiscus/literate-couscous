#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <staticjson/staticjson.hpp>
#include <string>
#include <unordered_map>

#include "physicalcomponent.h"

class Object
{
    uint32_t id_;
    uint32_t type_;
    std::string name_;
    std::optional<std::unique_ptr<PhysicalComponent>> physical_;
    bool is_stackable_;
    std::optional<uint32_t> quantity_;

public:
    Object(uint32_t id = 0, uint32_t type = 0, std::string name = "");

    uint32_t get_id() const;
    uint32_t get_type() const;
    std::string get_name() const;
    bool get_is_stackable() const;
    uint32_t get_quantity() const;

    PhysicalComponent* get_physical_component();
    const PhysicalComponent* get_physical_component() const;

    void set_physical_component(std::unique_ptr<PhysicalComponent> component);

    void set_is_stackable(bool value);
    void change_quantity(int32_t value);
    void set_quantity(uint32_t value);

    std::unique_ptr<Object> clone() const;

    void staticjson_init(staticjson::ObjectHandler *h);

    //bool operator=(const Object& rhs) const;
};