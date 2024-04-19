#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "assertion.h"

int Texture::globalIndex = 0;

Texture::Texture(const char* path) {
    ASSERT_MSG(Texture::globalIndex < 30, "Cannot have more than 32 textures");

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);  

    const stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);

    ASSERT_MSG(data, "Failed to load texture");

    int type = channels == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    index = globalIndex++; // Grabs current global index, increments it

    stbi_image_free((void*)data);
}

Texture::~Texture() {
    glDeleteTextures(1, &handle);
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, handle);
}
