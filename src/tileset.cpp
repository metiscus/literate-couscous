#include "tileset.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

Tileset::Tileset()
    : size_(0, 0)
{
    ;
}

void Tileset::load(const std::string& filename)
{
    std::string image_filename;

    std::ifstream infile (filename.c_str());
    if(infile.is_open())
    {
        infile>>image_filename;

        if(texture_.loadFromFile(image_filename))
        {
            size_ = texture_.getSize();
        }
        else
        {
            assert(false);
        }

        // load the subimage coords
        uint32_t tile_count = 0;
        infile>>tile_count;
        for(uint32_t ii=0; ii<tile_count; ++ii)
        {
            sf::IntRect rect;
            std::string name;
            infile >> name;
            infile >> rect.left;
            infile >> rect.top;
            infile >> rect.width;
            infile >> rect.height;

            extents_[ii] = rect;
            names_[name] = ii;

            std::cerr<<"["<<name<<"]\t"<<rect.left<<","<<rect.top<<","<<rect.width<<","<<rect.height<<"\n";
        }

        infile.close();
    }
}

sf::Vector2u Tileset::get_size() const
{
    return size_;
}

sf::IntRect Tileset::lookup_tile(uint32_t id) const
{
    sf::IntRect r;
    auto itr = extents_.find(id);
    if(itr != extents_.end())
    {
        r = itr->second;
    }

    return r;
}

sf::IntRect Tileset::lookup_tile(std::string name) const
{
    return lookup_tile(lookup_tile_index(name));
}

uint32_t Tileset::lookup_tile_index(std::string name) const
{
    auto itr = names_.find(name);
    if(itr != names_.end())
    {
        return itr->second;
    }

    return -1;
}