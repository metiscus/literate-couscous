#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

class Object;
class Inventory
{
    std::map<uint32_t, std::unique_ptr<Object>> objects_;

public:
    Inventory() = default;
    Inventory(const Inventory&) = delete;
    ~Inventory() = default;

    //TODO: remove this later
    void operator=(const Inventory&) = delete;

    bool contains_object(uint32_t type) const;
    uint32_t count_object(uint32_t type) const;
    const Object* peek_object(uint32_t type) const;
    Object* get_object(uint32_t type);
    std::unique_ptr<Object> remove_object(uint32_t type, uint32_t count = 1);
    void add_object(std::unique_ptr<Object> obj);

    float get_contained_weight() const;
    float get_contained_volume() const;
};