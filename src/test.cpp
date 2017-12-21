#include "object.h"
#include "physicalcomponent.h"
#include "inventory.h"
#include "character.h"
#include <staticjson/staticjson.hpp>
#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib>

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

    Character chr2;
    staticjson::from_json_string(chrstr.c_str(), &chr2, nullptr);

#if 0
    int width  = 100;
    int height = 50;
    int depth  = 10;
    std::set<int> points;
    //int index = x + y * (width + depth) + z * depth;
    for(int i=0; i<100; ++i)
    {
        for(int j=0; j<50; ++j)
        {
            for(int k=0; k<10; ++k)
            {
                int index = i * (width * depth) + j * depth + k;
                std::cerr<<"["<<j<<","<<i<<"]\t"<<index<<"\n";
                if(points.count(index))
                {
                    abort();
                }
                else
                {
                    points.insert(index);
                }
            }
        }
    }
#endif

    return 0;
}