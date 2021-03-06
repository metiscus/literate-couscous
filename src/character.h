#pragma once

#include "attributes.h"
#include <cstdint>
#include "inventory.h"
#include <staticjson/staticjson.hpp>
#include <string>


class Object;
class Character
{
    uint32_t id_;
    uint32_t type_;
    std::string name_;

    uint32_t race_id_;
    Attributes attributes_;

    Inventory inventory_;

public:
    Character(uint32_t id = 0);

    uint32_t    get_id() const;
    uint32_t    get_type() const;
    std::string get_name() const;
    uint32_t    get_race_id() const;
    const Attributes& get_attributes() const;
    Attributes& get_attributes();

    void set_type(uint32_t type);
    void set_name(const std::string& name);
    void set_race_id(uint32_t id);
    void set_attributes(Attributes atts);

    Inventory& get_inventory();
    const Inventory& get_inventory() const;

    void staticjson_init(staticjson::ObjectHandler *h);
};