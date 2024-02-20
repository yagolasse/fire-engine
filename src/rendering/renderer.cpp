#include "renderer.h"

#include <glad/glad.h>
#include <iostream>
#include <vec4.hpp>

void Renderer::init() {
    if (!gladLoadGL()) {
        std::cerr << "Could not initialize Glad/load GL!" << std::endl;
    }
}

void Renderer::setClearColor() {
    glClearColor(1.0, 0.0, 0.0, 1.0);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}
