#include "simtime.h"
#include <cassert>
#include <iostream>
#include <sstream>

namespace {
    inline bool is_leap_year(uint32_t year)
    {
        bool div_4 = (year % 4 == 0);
        bool div_100 = (year % 100 == 0);
        bool div_400 = (year % 400 == 0);;
        return (div_4 && (!div_100 || div_400));
    }

    inline uint32_t compute_month_length(uint32_t month, uint32_t year)
    {
        uint32_t month_length = 31;
        switch(month)
        {
            case 1:
            {
                if(is_leap_year(year))
                    month_length = 29; // leap years
                else
                    month_length = 28;
                break;
            }

            case 3:
            case 5:
            case 8:
            case 10:
                month_length = 30;
                break;

            default:
                month_length = 31;
        }

        return month_length;
    }

    inline uint32_t compute_day_in_year(uint32_t year, uint32_t month, uint32_t day)
    {
        uint32_t day_in_year = day;
        for(uint32_t i=0; i<month; ++i)
        {
            day_in_year += compute_month_length(i, year);
        }
        return day_in_year;
    }

    inline uint32_t R(uint32_t l, uint32_t r)
    {
        return l % r;
    }

    inline std::string number_string(uint32_t num)
    {
        std::stringstream ss;
        ss<<num;
        
        uint32_t last_digit = num % 10;
        switch(last_digit)
        {
            case 1: ss<<"st"; break;
            case 2: ss<<"nd"; break;
            case 3: ss<<"rd"; break;
            default: ss<<"th"; break;
        }

        return ss.str();
    }
}

Simtime::Simtime(uint32_t year_, uint32_t month_, uint32_t day_, uint32_t hour_, uint32_t minute_, uint32_t second_)
{
    set(year_, month_, day_, hour_, minute_, second_);
}

void Simtime::set(uint32_t year_, uint32_t month_, uint32_t day_, uint32_t hour_, uint32_t minute_, uint32_t second_)
{
    year = year_;
    day = day_;
    month = month_;
    hour = hour_;
    minute = minute_;
    second = second_;

    assert(day < compute_month_length(month, year));
    assert(hour < 24);
    assert(minute < 60);
    assert(second < 60);
}

void Simtime::advance(uint32_t year_, uint32_t month_, uint32_t day_, uint32_t hour_, uint32_t minute_, uint32_t second_)
{
    year += year_;
    day += day_;
    month += month_;
    hour += hour_;
    minute += minute_;
    second += second_;

    while(second >= 60)
    {
        second -= 60;
        minute += 1;
    }

    while(minute >= 60)
    {
        minute -= 60;
        hour += 1;
    }

    while(hour >= 24)
    {
        hour -= 24;
        day += 1;
    }

    while(month >= 12)
    {
        month -= 12;
        year += 1;
    }

    for(uint32_t month_length = compute_month_length(month, year); day >= month_length; )
    {
        if(day >= month_length)
        {
            day -= month_length;
            month += 1;
        }

        while(month >= 12)
        {
            month -= 12;
            year += 1;
        }

        month_length = compute_month_length(month, year);
    }
}

char const* Simtime::get_day() const
{
    uint32_t jan_1_day = R(1 + 5*R(year - 1, 4) + 4*R(year - 1, 100) + 6*R(year - 1, 400), 7);
    uint32_t day_in_year = compute_day_in_year(year, month, day);

    uint32_t the_day = R(R(day_in_year, 7) + jan_1_day, 7);
    switch(the_day)
    {
        case 0: return "Sunday"; break;
        case 1: return "Monday"; break;
        case 2: return "Tuesday"; break;
        case 3: return "Wednesday"; break;
        case 4: return "Thursday"; break;
        case 5: return "Friday"; break;
        case 6: return "Saturday"; break;
        default:
            assert(false);
            break;
    }
}

char const* Simtime::get_month() const
{
    switch(month)
    {
        case 0: return "January"; break;
        case 1: return "February"; break;
        case 2: return "March"; break;
        case 3: return "April"; break;
        case 4: return "May"; break;
        case 5: return "June"; break;
        case 6: return "July"; break;
        case 7: return "August"; break;
        case 8: return "September"; break;
        case 9: return "October"; break;
        case 10: return "November"; break;
        case 11: return "December"; break;
        default:
            assert(false);
            break;
    }
}

std::string Simtime::get_date() const
{
    std::stringstream date;
    date<<get_day()<<" the "<<number_string(day)<<" of "<<get_month()<<" in the year "<<year;
    return date.str();
}

void Simtime::staticjson_init(staticjson::ObjectHandler *h)
{
    h->add_property("year", &year);
    h->add_property("day", &day);
    h->add_property("month", &month);
    h->add_property("hour", &hour);
    h->add_property("minute", &minute);
    h->add_property("second", &second);
}