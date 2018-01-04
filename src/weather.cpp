#include "weather.h"

#include <cmath>

void Weather::set_location_info(LocationInfo location)
{
    location_ = location;
}

void Weather::set_time(Simtime time_)
{
    time_ = time_;
}

float Weather::get_mean_daylight_hours() const
{
    double P = asin(.39795*cos(.2163108 + 2.0*atan(.9671396*tan(.00860 * (double(time_.get_julian_day())-186.0)))));
    double length = 24.0 - (24.0/M_PI)*acos( (sin(0.8333*M_PI/180.0) + sin(location_.latitude*M_PI/180.0)*sin(P)) / (cos(location_.latitude*M_PI/180.0)*cos(P)));
    return length;
}

float Weather::compute_day_max_temperature()
{
    return location_.max_temperature.a * sinf((float(time_.month) + 1.f) * M_PI / 6.f) + location_.max_temperature.b;
}

float Weather::compute_day_min_temperature()
{
    return location_.min_temperature.a * sinf((float(time_.month) + 1.f) * M_PI / 6.f) + location_.min_temperature.b;
}
