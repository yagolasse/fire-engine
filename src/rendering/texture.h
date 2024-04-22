#pragma once

#include <glad/glad.h>

class Texture {
   private:
    unsigned int handle;
    int width;
    int height;
    int channels;

   public:
    Texture(const char* path);
    ~Texture();

    void bind() const;

    inline unsigned int getHandle() const {
        return handle;
    }
};
