#include "application.h"

#include <imgui.h>

#include <iostream>

#include "batch_renderer.h"
#include "debug_ui.h"
#include "input.h"
#include "renderer.h"
#include "scene.h"
#include "texture_storage.h"
#include "window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Application::Application() {
    // First, window context
    window = new Window(1280, 720, "Fire Engine");

    Input::init(window->getHandle());

    // Then, graphics API
    Renderer::init((GLADloadproc)glfwGetProcAddress);
    Renderer::setClearColor();

    DebugUi::init(window->getHandle());  // TODO: Move into scene

    // Lastly, GPU buffers
    batchRenderer = std::make_shared<BatchRenderer>();

    textureStorage = std::make_shared<TextureStorage>();
}

Application::~Application() {
    delete scene;
    delete window;
}

void Application::init() {
}

void Application::run() {
    double frameTime = glfwGetTime();
    double plotCounter = 0;
    double debugFrameTime = 0;

    scene->start();

    while (!window->shouldClose()) {
        double deltaTime = glfwGetTime();
        double currentFrameTime = deltaTime - frameTime;

        window->pollEvents();

        /// App Code

        DebugUi::beginFrame();  // TODO: Move into scene

        textureStorage->bind();

        plotCounter += currentFrameTime;

        if (plotCounter > 0.1) {
            plotCounter = 0.0;
            debugFrameTime = currentFrameTime;
        }

        ImGui::Text("%.2f ms", debugFrameTime * 1000.0);  // TODO: Move into scene

        scene->update(currentFrameTime);
        /// End App Code

        scene->render();

        DebugUi::draw();  // TODO: Move into scene

        window->swapBuffers();

        frameTime = deltaTime;
    }

    DebugUi::dispose();  // TODO: Move into scene
}
