#include "renderer.h"

#include <glad/glad.h>

#include <iostream>
#include <vec4.hpp>

#include "assertion.h"


void Renderer::init() {
    ASSERT_MSG(gladLoadGL(), "Could not initialize Glad/load GL!");
}

void Renderer::setClearColor() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
