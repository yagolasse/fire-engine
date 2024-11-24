#include "texture_storage.h"

#include <stb_image.h>

#include <glad/glad.h>

#include <vector>

#include "assertion.h"

TextureStorage::TextureStorage() : currentIndex(0) {
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D_ARRAY, handle);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, maxWidth, maxHeight, maxTextures, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureStorage::~TextureStorage() {
    glDeleteTextures(1, &handle);
}

TextureData TextureStorage::loadTexture(std::string path) {
    currentIndex++;

    std::vector<std::uint32_t> clearData(maxWidth * maxHeight, 0);

    stbi_set_flip_vertically_on_load(true);

    int width;
    int height;
    int channels;

    const stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    ASSERT_MSG(data, "Failed to load texture");

    glBindTexture(GL_TEXTURE_2D_ARRAY, handle);

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, currentIndex, maxWidth, maxHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, &clearData[0]);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, currentIndex, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    stbi_image_free((void*)data);

    return TextureData{
        width,
        height,
        currentIndex,
        glm::vec2{(float)width / maxWidth, (float)height / maxHeight},
    };
}

void TextureStorage::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, handle);
}
