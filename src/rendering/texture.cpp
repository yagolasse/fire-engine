#include "texture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

#include "assertion.h"

int Texture::currentBindingIndex = 0;

Texture::Texture(const char* path) {
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

    stbi_image_free((void*)data);

    bindingIndex = ++Texture::currentBindingIndex;
}

Texture::~Texture() {
    glDeleteTextures(1, &handle);
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + bindingIndex);
    glBindTexture(GL_TEXTURE_2D, handle);
}
