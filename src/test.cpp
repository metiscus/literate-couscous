#include "object.h"
#include "physicalcomponent.h"
#include "inventory.h"
#include "character.h"
#include <staticjson/staticjson.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    auto obj = std::make_unique<Object>(0, 1, "sword");
    auto physical_component = std::make_unique<PhysicalComponent>( 10.0, 1.5, 10 );
    obj->set_physical_component(std::move(physical_component));

    std::string sword = staticjson::to_json_string(*obj);
    std::cout<<sword<<"\n";


    Character chr;

    Inventory &inv = chr.get_inventory();
    inv.add_object(obj->clone());

    std::string chrstr = staticjson::to_json_string(chr);
    std::cout<<chrstr<<"\n";

    return 0;
}