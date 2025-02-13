#include "asset_loader.hpp"

#include "texture.hpp"

AssetLoader::AssetLoader() : textures({}) {
}

std::shared_ptr<Texture> AssetLoader::loadTexture(std::string path) {
    std::shared_ptr<Texture> result = textures[path];
    if (result == nullptr) {
        result = std::make_shared<Texture>((resourcesPath + path).c_str());
        textures[path] = result;
    }
    return result;
}
