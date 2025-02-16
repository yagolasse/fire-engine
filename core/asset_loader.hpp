#ifndef ASSET_LOADER_HPP
#define ASSET_LOADER_HPP

#include <memory>
#include <string>
#include <unordered_map>

class Texture;

class AssetLoader {
   private:
    const std::string resourcesPath = "../resources/";
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

   public:
    AssetLoader();

    std::shared_ptr<Texture> loadTexture(std::string path);
};

#endif
