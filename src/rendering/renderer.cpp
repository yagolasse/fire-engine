#include "renderer.h"

#include <iostream>
#include <vec4.hpp>

#include <glad/glad.h>

#include "assertion.h"

void Renderer::init(GLADloadproc loadProcedure) {
    ASSERT_MSG(gladLoadGLLoader(loadProcedure), "Could not initialize Glad/load GL!");

    glEnable(GL_DEPTH_TEST);
}

void Renderer::setClearColor() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
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
