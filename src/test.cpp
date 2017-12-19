#include "object.h"
#include "physicalcomponent.h"
#include <staticjson/staticjson.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
	Object obj(0, 1, "sword");
	auto physical_component = std::make_unique<PhysicalComponent>( 10.0, 1.5, 10 );
	obj.set_physical_component(std::move(physical_component));

	std::string sword = staticjson::to_json_string(obj);
	std::cout<<sword<<"\n";

	return 0;
}