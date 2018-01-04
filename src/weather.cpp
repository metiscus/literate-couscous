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
    constexpr float data[13][12] = {
        { 0.15, 0.20, .26, .32, .38, .41, .40, .34, .28, .22, .17, .13 },
        { 0.17, 0.21, .26, .32, .36, .39, .38, .33, .28, .23, .18, .16 },
        { 0.19, 0.23, .27, .31, .34, .36, .35, .32, .28, .24, .20, .18 },
        { 0.20, 0.23, .27, .30, .34, .35, .34, .32, .28, .24, .21, .20 },
        { 0.22, 0.24, .27, .30, .32, .34, .33, .31, .28, .25, .22, .21 },
        { 0.23, 0.25, .27, .29, .31, .33, .32, .30, .28, .25, .23, .22 },
        { 0.24, 0.25, .27, .29, .31, .32, .31, .30, .28, .26, .24, .23 },
        { 0.24, 0.26, .27, .29, .30, .31, .31, .29, .28, .26, .25, .24 },
        { 0.25, 0.26, .27, .28, .29, .30, .30, .29, .28, .26, .25, .25 },
        { 0.26, 0.26, .27, .28, .29, .29, .29, .28, .28, .27, .26, .25 },
        { 0.26, 0.27, .27, .28, .29, .29, .29, .28, .28, .27, .26, .26 },
        { 0.27, 0.27, .27, .28, .28, .28, .48, .28, .28, .27, .27, .27 },
        { 0.27, 0.27, .27, .27, .27, .27, .27, .27, .27, .27, .27, .27 }
    };

    float latitude = location_.latitude;
    uint32_t month = time_.month;

    int latitude_index = 0;
    if(latitude < 0) 
    {
        latitude = -1.f * latitude;
        month = (month + 6) % 12;
    }

    if(latitude >= 60) latitude_index = 0;
    latitude_index = 60 - int(latitude) / 5;
    
    return data[latitude_index][month];
}

float Weather::compute_day_max_temperature()
{
    return location_.max_temperature.a * sinf((float(time_.month) + 1.f) * M_PI / 6.f) + location_.max_temperature.b;
}

float Weather::compute_day_min_temperature()
{
    return location_.min_temperature.a * sinf((float(time_.month) + 1.f) * M_PI / 6.f) + location_.min_temperature.b;
}
