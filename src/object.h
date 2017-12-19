#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <staticjson/staticjson.hpp>
#include <string>
#include <unordered_map>

class PhysicalComponent;

class Object
{
    uint32_t id_;
    uint32_t type_;
    std::string name_;
    std::optional<std::unique_ptr<PhysicalComponent>> physical_;
    bool is_stackable_;

public:
    Object(uint32_t id, uint32_t type, std::string name);

    uint32_t get_id() const;
    uint32_t get_type() const;
    std::string get_name() const;
    bool get_is_stackable() const;

    PhysicalComponent* get_physical_component();

    void set_physical_component(std::unique_ptr<PhysicalComponent> component);

    void set_is_stackable(bool value);

    std::unique_ptr<Object> clone() const;

    void staticjson_init(staticjson::ObjectHandler *h);
};