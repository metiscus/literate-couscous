#pragma once

#include "simtime.h"

struct CurveData
{
    float a;
    float b;
};

struct LocationInfo
{
    float latitude;
    float longitude;
    CurveData max_temperature;
    CurveData min_temperature;
};

class Weather
{
    Simtime time_;
    LocationInfo location_;

public:
    void set_location_info(LocationInfo location);
    void set_time(Simtime time);

    float get_mean_daylight_hours() const;

    float compute_day_max_temperature();
    float compute_day_min_temperature();
};