#include "texture_storage.hpp"

#include <glad/glad.h>
#include <stb_image.h>

#include <unordered_map>
#include <vector>

#include "assertion.hpp"
#include "texture_data.hpp"

TextureStorage* TextureStorage::instance = nullptr;

TextureStorage* TextureStorage::getInstance() {
    if (instance == nullptr) {
        instance = new TextureStorage();
    }
    return instance;
}

void TextureStorage::disposeInstance() {
    delete instance;
}

TextureStorage::TextureStorage() : currentIndex(0) {
}

TextureStorage::~TextureStorage() {
    for (std::pair<const std::string, TextureData*>& it : cache) {
        delete it.second;
    }
    glDeleteTextures(1, &handle);
}

TextureData* TextureStorage::loadTexture(std::string path) {
    if (cache.find(path) != cache.end()) {
        return cache[path];
    }

    currentIndex++;

    std::vector<std::uint32_t> clearData(maxWidth * maxHeight, 0);

    stbi_set_flip_vertically_on_load(true);

    int width;
    int height;
    int channels;

    const stbi_uc* data = stbi_load((resourcesPath + path).c_str(), &width, &height, &channels, 0);

    ASSERT_MSG(data, "Failed to load texture");

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D_ARRAY, handle);

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, currentIndex, maxWidth, maxHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, &clearData[0]);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, currentIndex, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    stbi_image_free((void*)data);

    TextureData* textureData = new TextureData{
        width,
        height,
        currentIndex,
        glm::vec2{(float)width / maxWidth, (float)height / maxHeight},
    };

    cache[path] = textureData;

    return textureData;
}

void TextureStorage::init() {
    glGenTextures(1, &handle);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D_ARRAY, handle);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, maxWidth, maxHeight, maxTextures, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    cache = {};
}

void TextureStorage::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, handle);
}
