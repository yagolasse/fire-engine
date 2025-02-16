#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP

#include <unordered_map>
#include <string>

class TextureData;

class TextureStorage {
   private:
    const std::string resourcesPath = "../resources/";
    
    static TextureStorage* instance;

    const int maxTextures = 64;
    const int maxWidth = 512;
    const int maxHeight = 512;
    unsigned int handle;
    int currentIndex;

    std::unordered_map<std::string, TextureData*> cache;

    TextureStorage();
    ~TextureStorage();

   public:
    static TextureStorage* getInstance();
    static void disposeInstance();

    TextureData* loadTexture(std::string path);
    void init();
    void bind() const;
};

#endif
