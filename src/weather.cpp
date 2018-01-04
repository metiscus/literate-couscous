#include "weather.h"

#include <iostream>
#include <cmath>

void Weather::set_location_info(LocationInfo location)
{
    location_ = location;
}

void Weather::set_time(Simtime time_)
{
    this->time_ = time_;
}

float Weather::get_mean_daylight_hours() const
{
    // http://mathforum.org/library/drmath/view/56478.html
    double P = asin(.39795*cos(.2163108 + 2.0*atan(.9671396*tan(.00860 * (double(time_.get_julian_day())-186.0)))));
    double length = 24.0 - (24.0/M_PI)*acos( (sin(0.8333*M_PI/180.0) + sin(location_.latitude*M_PI/180.0)*sin(P)) / (cos(location_.latitude*M_PI/180.0)*cos(P)));
    return length;
}

float Weather::compute_day_max_temperature() const
{
    return location_.max_temperature.a * sinf((float(time_.month) + 1.f) * M_PI / 6.f) + location_.max_temperature.b;
}

float Weather::compute_day_min_temperature() const
{
    return location_.min_temperature.a * sinf((float(time_.month) + 1.f) * M_PI / 6.f) + location_.min_temperature.b;
}

float Weather::compute_temperature() const
{
    const float temperature_offset = 2.0;
    const float max_temp = compute_day_max_temperature();
    const float min_temp = compute_day_min_temperature();
    const float temp_slope = (max_temp - min_temp) / 12.0f;

    float time_fraction = float(time_.hour) - temperature_offset + float(time_.minute) / 60.0f;
    time_fraction = time_fraction - 12.0f;// map to [-12 , 12]
    time_fraction = 12.0f - fabs(time_fraction);

    return min_temp + temp_slope * time_fraction;
}