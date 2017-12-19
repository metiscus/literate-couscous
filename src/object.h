#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

class Object
{
    uint32_t id_;
    uint32_t type_;
    std::string name_;

public:
    Object(uint32_t id, uint32_t type, std::string name);

    uint32_t get_id() const;
    uint32_t get_type() const;
    std::string get_name() const;
};