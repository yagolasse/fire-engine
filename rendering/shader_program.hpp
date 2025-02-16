#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <glm.hpp>
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
    void setVec3(const char* name, glm::vec3 value) const;
    void setMat4(const char* name, const float* value) const;

    inline GLuint getHandle() const {
        return handle;
    }
};

#endif
