#include "renderer.h"

#include <glad/glad.h>

#include <iostream>
#include <vec4.hpp>

#include "assertion.h"

void Renderer::init(GLADloadproc loadProcedure) {
    ASSERT_MSG(gladLoadGLLoader(loadProcedure), "Could not initialize Glad/load GL!");

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
        },
        0
    );

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void Renderer::setClearColor() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(int elementCount) {
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
}

void Renderer::makeTextureActive(int index) {
    glActiveTexture(GL_TEXTURE0 + index);
}

void Renderer::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}
