#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

class Shader {
   private:
    GLuint handle;

   public:
    Shader(GLenum type, const GLchar* source);
    ~Shader();

    inline GLuint getHandle() const {
        return handle;
    }
};

#endif
