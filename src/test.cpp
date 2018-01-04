#include "object.h"
#include "physicalcomponent.h"
#include "weaponcomponent.h"
#include "inventory.h"
#include "character.h"
#include <staticjson/staticjson.hpp>
#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib>
#include "map.h"

#include "game.h"

int main(int argc, char** argv)
{
    auto obj = std::make_unique<Object>(0, 1, "sword");
    obj->set_physical_component(std::move(std::make_unique<PhysicalComponent>( 10.0, 1.5, 10 )));
    obj->set_weapon_component(std::move(std::make_unique<WeaponComponent>(WeaponType::Melee, 0, 0, 0)));

    std::string sword = staticjson::to_json_string(*obj);
    std::cout<<sword<<"\n";


    Character chr;

    Inventory &inv = chr.get_inventory();
    inv.add_object(obj->clone());

    std::string chrstr = staticjson::to_json_string(chr);
    std::cout<<chrstr<<"\n";

    Character chr2;
    staticjson::from_json_string(chrstr.c_str(), &chr2, nullptr);

    constexpr int size = 128;
    Map m(size, size, 1);

    for(int i=0; i<size; ++i)
    {
        for(int j=0; j<size; ++j)
        {
            m.at(i, j).set_terrain(TerrainId::Outdoor_Grass);
        }
    }

    std::string chrstr2 = staticjson::to_json_string(m);
    //std::cout<<chrstr2<<"\n";

    Game g;

    return 0;
}