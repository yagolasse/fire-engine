#include "shader.hpp"

#include <cstddef>
#include <iostream>

#include <glad/glad.h>

Shader::Shader(Type type) {
    handle = glCreateShader((GLenum)type);
}

Shader::~Shader() {
    glDeleteShader(handle);
}

void Shader::compile(const std::string& source) const {
    const char * cStrSource = source.c_str();
    glShaderSource(handle, 1, &cStrSource, NULL);
    glCompileShader(handle);

    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(handle, 512, NULL, infoLog);
        std::cerr << "Error compiling shader: " << infoLog << std::endl;
    }
}
