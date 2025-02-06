#include "asset_loader.h"

#include "texture.h"

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
