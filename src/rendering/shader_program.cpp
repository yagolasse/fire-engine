#include "shader_program.h"

#include  "shader.h"

#include <iostream>

ShaderProgram::ShaderProgram(std::unique_ptr<Shader> vertexShader, std::unique_ptr<Shader> fragmentShader) {
    handle = glCreateProgram();

    glAttachShader(handle, vertexShader->getHandle());
    glAttachShader(handle, fragmentShader->getHandle());
    glLinkProgram(handle);

    GLint success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);

    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(handle, 512, NULL, infoLog);        
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
    }
}

void ShaderProgram::bind() const {
    glUseProgram(handle);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(handle);
}