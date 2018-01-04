#pragma once

#include <cstdint>
#include <string>
#include <staticjson/staticjson.hpp>

struct Simtime
{
    uint32_t year;
    uint32_t day;
    uint32_t month;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;

    Simtime(uint32_t year = 2000,  uint32_t month = 1, uint32_t day = 1, uint32_t hour = 1, uint32_t minute = 1, uint32_t second = 0);

    void set(uint32_t year,  uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);

    void advance(uint32_t year,  uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);

    char const* get_day() const;
    char const* get_month() const;

    std::string get_date() const;

    void staticjson_init(staticjson::ObjectHandler *h);
};