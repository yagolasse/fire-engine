#include <GLFW/glfw3.h>
#include <stdio.h>

#include "core/window.h"
#include "rendering/renderer.h"

int main(int argc, char* argv[]) {
    Window window(1280, 720, "Hello Window");

    Renderer::init();

    Renderer::setClearColor();

    while (!window.shouldClose()) {
        Renderer::clear();

        window.pollEvents();

        window.swapBuffers();
    }

    return 0;
}
