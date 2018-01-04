#pragma once

#include "attributes.h"
#include <cstdint>
#include <staticjson/staticjson.hpp>
#include <string>

class Race
{
    uint32_t id_;
    std::string name_;
    std::string plural_;
    Attributes attributes_;

public:
    Race(uint32_t id = 0, std::string name = "invalid", std::string plural = "invalids")
        : id_(id), name_(name), plural_(plural)
    {
        ;
    }

    inline uint32_t get_id() const 
    { 
        return id_; 
    }

    inline std::string get_name() const 
    { 
        return name_; 
    }

    inline std::string get_plural() const 
    { 
        return plural_; 
    }

    Attributes get_attributes() const 
    { 
        return attributes_; 
    }

    void set_attributes(Attributes attributes) 
    { 
        attributes_ = attributes; 
    }

    void staticjson_init(staticjson::ObjectHandler *h)
    {
        h->add_property("id", &id_);
        h->add_property("name", &name_);
        h->add_property("plural", &plural_);
        h->add_property("attributes", &attributes_);
    }
};