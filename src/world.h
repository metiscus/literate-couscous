#pragma once

#include <cstdint>
#include <map>
#include "map.h"
#include <memory>
#include "player.h"
#include "simtime.h"
#include "weather.h"

class World
{
    std::shared_ptr<Player> player_;
    Simtime time_;
    Weather weather_;
    std::map<uint32_t, std::shared_ptr<Map>> maps_;
    uint32_t current_map_;

public:
    void new_game(std::shared_ptr<Player> player);

    void set_player(std::shared_ptr<Player> player) { player_ = player; }
    std::shared_ptr<Player> get_player() { return player_; }

    Simtime& get_time() { return time_; }
    const Simtime& get_time() const { return time_; }
    void set_time(const Simtime& time) { time_ = time; }

    Weather& get_weather() { return weather_; }
    const Weather& get_weather() const { return weather_; }
    void set_weather(const Weather& weather) { weather_ = weather; }

};