#include "inventory.h"
#include "object.h"
#include "physicalcomponent.h"

bool Inventory::contains_object(uint32_t type) const
{
    return objects_.count(type);
}

uint32_t Inventory::count_object(uint32_t type) const
{
    auto itr = objects_.find(type);
    if(itr == objects_.end())
    {
        return 0;
    }
    else
    {
        return itr->second->get_quantity();
    }
}

const Object* Inventory::peek_object(uint32_t type) const
{
    auto itr = objects_.find(type);
    if(itr == objects_.end())
    {
        return nullptr;
    }
    else
    {
        return itr->second.get();
    }
}

Object* Inventory::get_object(uint32_t type)
{
    auto itr = objects_.find(type);
    if(itr == objects_.end())
    {
        return nullptr;
    }
    else
    {
        return itr->second.get();
    }
}

std::unique_ptr<Object> Inventory::remove_object(uint32_t type, uint32_t count)
{
    // Need to handle several cases here:
    //   we have none of the object
    //   we have more than the requested amount
    //   we have less than the requested amount
    //   we have exactly the requested amount

    auto itr = objects_.find(type);
    // We have none of the object
    if(itr == objects_.end())
    {
        return std::unique_ptr<Object>();
    }

    uint32_t qty_stock = itr->second->get_quantity();
    if(qty_stock > count)
    {
        // We have more than the requested amount
        //-In this case we clone a new object with the requested count
        //-and remove the quantity from the object in the map
        itr->second->change_quantity(-int32_t(count));

        // Make the object to return
        auto obj = itr->second->clone();
        obj->set_quantity(count);
        return obj;
    }
    else 
    {
        // We have less than the requested amount
        // We have exactly the requested amount
        auto obj = std::move(itr->second);
        objects_.erase(itr);
        return obj;
    }
}

void Inventory::add_object(std::unique_ptr<Object> obj)
{
    // If the object exists already we merge it otherwise just simply add it
    auto itr = objects_.find(obj->get_type());
    
    if(itr == objects_.end())
    {
        objects_.emplace(std::make_pair(obj->get_type(), std::move(obj)));
    }
    else
    {
        auto tmp = std::move(obj);
        itr->second->change_quantity(obj->get_quantity());
    }
}

float Inventory::get_contained_weight() const
{
    float weight = 0.0;
    for(const auto& itr : objects_)
    {
        auto physical = itr.second->get_physical_component();
        if(physical)
        {
            weight += itr.second->get_quantity() * physical->get_weight();
        }
    }
    return weight;
}

float Inventory::get_contained_volume() const
{
    float volume = 0.0;
    for(const auto& itr : objects_)
    {
        auto physical = itr.second->get_physical_component();
        if(physical)
        {
            volume += itr.second->get_quantity() * physical->get_volume();
        }
    }
    return volume;
}