#ifndef TEXTURE_DATA_HPP
#define TEXTURE_DATA_HPP

#include <glm.hpp>

struct TextureData {
    int width;
    int height;
    int index;
    glm::vec2 maxUV;
};

#endif
