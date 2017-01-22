#include "TextureCache.h"

#include <iostream>
#include "Core.h"


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

Texture* TextureCache::getTexture(std::string texturePath, fileExtension flag) {

    auto it = m_TextureMap.find(texturePath);

    if (it == m_TextureMap.end())
    {
        if (fileExist(texturePath)) 
        {
            Texture* newTexture = new Texture;
            newTexture->loadData(texturePath, flag);
            std::pair<std::string, Texture*> newPair(texturePath, newTexture);
            m_TextureMap.insert(newPair);
            //std::cout << "Used Cached Texture" << std::endl;
            return newTexture;
        }
        else {
            std::cout << texturePath << "  texture not loaded" << std::endl;
            return nullptr;
        }
    }

    //std::cout << "Loaded Texture" << std::endl;
    return it->second;
}

