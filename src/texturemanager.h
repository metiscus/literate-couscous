#pragma once
#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>


typedef std::shared_ptr<sf::Texture> TexturePtr;
class TextureManager
{
private:

    std::map<std::string, TexturePtr> textures_;
    
public:

    TextureManager() = default;
    ~TextureManager() = default;

    void load_texture(const std::string& name, const std::string& filename);
    
    TexturePtr get_texture(const std::string& name);
};

#endif // TEXTUREMANAGER_H_INCLUDED
