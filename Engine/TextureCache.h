#pragma once
#include <map>
#include "Texture.h"


class TextureCache
{
public:
    TextureCache();
    ~TextureCache();

    Texture* getTexture(std::string texturePath, fileExtension flag = JPG);

private:
    std::map<std::string, Texture*> m_TextureMap;
};
