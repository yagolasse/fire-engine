#pragma once

#include <glad/glad.h>

class Shader {
   private:
    GLuint handle;

   public:
    Shader(GLenum type, const char* source);
    ~Shader();

    void bind() const;
    void unbind() const;

    inline GLuint getHandle() const {
        return handle;
    }
};
