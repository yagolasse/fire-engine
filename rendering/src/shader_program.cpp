#include "shader_program.hpp"

#include <glad/glad.h>

#include <iostream>
#include <memory>

#include "error.hpp"
#include "shader.hpp"

ShaderProgram::ShaderProgram() {
    handle = glCreateProgram();
}

void ShaderProgram::bind() const {
    glUseProgram(handle);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

void ShaderProgram::linkShader(const std::string& vertexSource, const std::string& fragmentSource) const {
    Shader* vertexShader = new Shader(Shader::Type::VERTEX);
    Shader* fragmentShader = new Shader(Shader::Type::FRAGMENT);

    vertexShader->compile(vertexSource);
    fragmentShader->compile(fragmentSource);

    glAttachShader(handle, vertexShader->getHandle());
    glAttachShader(handle, fragmentShader->getHandle());
    glLinkProgram(handle);

    GLint success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(handle, 512, NULL, infoLog);
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
    }

    delete vertexShader;
    delete fragmentShader;
}

void ShaderProgram::setBool(const char* name, bool value) const {
    glUniform1i(glGetUniformLocation(handle, name), (int)value);
}

void ShaderProgram::setInt(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(handle, name), value);
}

void ShaderProgram::setFloat(const char* name, float value) const {
    glUniform1f(glGetUniformLocation(handle, name), value);
}

void ShaderProgram::setVec3(const char* name, glm::vec3 value) const {
    glUniform3f(glGetUniformLocation(handle, name), value.x, value.y, value.z);
}

void ShaderProgram::setMat4(const char* name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(handle, name), 1, GL_FALSE, value);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(handle);
}
