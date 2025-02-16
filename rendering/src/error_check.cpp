#include "error_check.hpp"

#include <glad/glad.h>

#include <iostream>

#ifdef ERROR_CHECK_AVAILABLE

void ErrorCheck::logOpenGlErrors() {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
}

#endif