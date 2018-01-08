#include "texturemanager.h"
#include <iostream>

void TextureManager::load_texture(const std::string& name, const std::string& filename)
{
    TexturePtr tex = std::make_shared<sf::Texture>();
    if(!tex->loadFromFile(filename))
    {
    	std::cerr<<"Failed to load texture '"<<filename<<"'\n";
    }
    
    textures_[name] = tex;
}
    
TexturePtr TextureManager::get_texture(const std::string& name)
{
    return textures_.at(name);
}
