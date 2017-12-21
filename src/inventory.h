#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include "object.h"
#include <string>
#include <vector>

#include <staticjson/staticjson.hpp>


class Inventory
{
    std::map<uint32_t, std::unique_ptr<Object>> objects_;

    friend struct staticjson::Converter<Inventory>;

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

namespace staticjson
{
template <>
struct Converter<Inventory>
{
    typedef std::vector<std::string> shadow_type; 
    // This typedef is a must. The shadow type is a C++ type 
    // that can be directly converted to and from JSON values.

    static std::unique_ptr<ErrorBase> from_shadow(const shadow_type& shadow, Inventory& value)
    {
        for(auto str : shadow)
        {
            std::unique_ptr<Object> obj;
            from_json_string(str.c_str(), &obj, nullptr);
            assert(obj);
            if(obj)
            {
                value.add_object(std::move(obj));
            }
        }
        return nullptr;
    }

    static void to_shadow(const Inventory& value, shadow_type& shadow)
    {
        for(const auto& obj : value.objects_)
        {
            shadow.push_back(to_json_string(*(obj.second.get())));
        }
    }
};
}