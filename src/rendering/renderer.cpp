#include "renderer.h"

#include <iostream>
#include <vec4.hpp>

#include "assertion.h"

void Renderer::init() {
    ASSERT_MSG(gladLoadGL(), "Could not initialize Glad/load GL!");
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam) { std::cerr << message << std::endl; },
                           nullptr);
}

void Renderer::setClearColor() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
