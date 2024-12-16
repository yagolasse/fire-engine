#include "application.h"

#include <imgui.h>

#include <iostream>

#include "debug_ui.h"
#include "renderer.h"
#include "texture_storage.h"
#include "scene.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Application::Application() {
    // First, window context
    window = std::make_unique<Window>(1280, 720, "Fire Engine");

    // Then, graphics API
    Renderer::init((GLADloadproc)glfwGetProcAddress);
    Renderer::setClearColor();

    DebugUi::init(window->getHandle());  // TODO: Move into scene

    // Lastly, GPU buffers
    batchRenderer = std::make_shared<BatchRenderer>();

    textureStorage = std::make_shared<TextureStorage>();
}

void Application::run() {
    Scene scene(batchRenderer, textureStorage);

    double frameTime = glfwGetTime();

    scene.onStart();

    while (!window->shouldClose()) {
        double deltaTime = glfwGetTime();

        window->pollEvents();

        /// App Code

        DebugUi::beginFrame();  // TODO: Move into scene

        textureStorage->bind();
        
        ImGui::Text("%.2f ms", (deltaTime - frameTime) * 1000.0);  // TODO: Move into scene

        scene.onUpdate(deltaTime - frameTime);
        /// End App Code

        DebugUi::draw();  // TODO: Move into scene

        window->swapBuffers();

        frameTime = deltaTime;
    }

    DebugUi::dispose();  // TODO: Move into scene
}
