#pragma once

#include <glad/glad.h>

#include <memory>

class Shader;

class ShaderProgram {
   private:
    GLuint handle;

   public:
    ShaderProgram(std::unique_ptr<Shader> vertexShader, std::unique_ptr<Shader> fragmentShader);
    ~ShaderProgram();

    void bind() const;
    void unbind() const;

    void setBool(const char* name, bool value) const;
    void setInt(const char* name, int value) const;
    void setFloat(const char* name, float value) const;

    inline GLuint getHandle() const {
        return handle;
    }
};
