#pragma once

#include <unordered_map>
#include <string>

#include "texture_data.h"

class TextureStorage {
   private:
    const int maxTextures = 64;
    const int maxWidth = 512;
    const int maxHeight = 512;
    unsigned int handle;
    int currentIndex;

    std::unordered_map<std::string, TextureData> cache;

   public:
    TextureStorage();
    ~TextureStorage();

    TextureData loadTexture(std::string path);
    void bind() const;
};
