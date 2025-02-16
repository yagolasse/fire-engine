#include "renderer.hpp"

#include <glad/glad.h>

#include <iostream>
#include <vec4.hpp>

#include "assertion.hpp"
#include "error_check.hpp"

Renderer* Renderer::instance = nullptr;

Renderer* Renderer::getInstance() {
    if (instance == nullptr) {
        instance = new Renderer();
    }
    return instance;
}

void Renderer::disposeInstance() {
    delete instance;
}

Renderer::Renderer() {
}

void Renderer::init(LoadProcedure loadProcedure) {
    ASSERT_MSG(gladLoadGLLoader(loadProcedure), "Could not initialize Glad/load GL!");

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::setClearColor() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
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
