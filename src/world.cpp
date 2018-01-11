#include "world.h"
#include "game.h"
#include "mapgen.h"

void World::new_game(std::shared_ptr<Player> player)
{

    player_ = player;

    //TODO: Eventually need to load this from somewhere
    LocationInfo here;
    here.latitude = -50.0f;
    here.max_temperature.a = 4.2f;
    here.max_temperature.b = 13.07f;
    here.min_temperature.a = 3.21f;
    here.min_temperature.b = 12.2f;

    weather_.set_location_info(here);
    weather_.set_time(time_);

    // Set the current map id and then generate it
    current_map_ = 0;

    // generate a map
    constexpr uint32_t map_size = 256;
    Mapgen map_gen(map_size, map_size, 1);

    auto map = map_gen.generate_outdoors_map(0);
    maps_.insert(std::make_pair(0, map));
}

std::shared_ptr<Map> World::get_current_map()
{
    return maps_[current_map_];
}