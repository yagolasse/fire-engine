#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <string>

class Shader {
   private:
    GLuint handle;

   public:
    enum class Type {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

    Shader(Type type);
    ~Shader();

    void compile(const std::string& source) const;

    inline GLuint getHandle() const {
        return handle;
    }
};

#endif
