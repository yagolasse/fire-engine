#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <glad/glad.h>

#include <glm.hpp>
#include <memory>

class Shader;

class ShaderProgram {
   private:
    GLuint handle;

   public:
    ShaderProgram();
    ~ShaderProgram();

    void bind() const;
    void unbind() const;

    void linkShader(const std::string& vertexSource, const std::string& fragmentSource) const;

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
