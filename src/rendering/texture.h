#pragma once

#include <glad/glad.h>

class Texture {
   private:
    GLuint handle;
    int width;
    int height;
    int channels;
    int index;
    static int globalIndex;

   public:
    Texture(const char* path);
    ~Texture();

    inline const int getIndex() const {
        return index;
    }
    void bind() const;
};
