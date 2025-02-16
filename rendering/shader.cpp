#include "shader.hpp"

#include <cstddef>
#include <iostream>

#include <glad/glad.h>

Shader::Shader(GLenum type, const GLchar* source) {
    handle = glCreateShader(type);

    glShaderSource(handle, 1, &source, NULL);
    glCompileShader(handle);

    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(handle, 512, NULL, infoLog);
        std::cerr << "Error compiling shader: " << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(handle);
}
