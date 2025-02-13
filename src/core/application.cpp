#include "application.hpp"

#include <imgui.h>

#include <iostream>

#include "batch_renderer.hpp"
#include "debug_ui.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "scene_manager.hpp"
#include "texture_storage.hpp"
#include "window.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Application::Application() {
    // First, window context
    window = new Window(1280, 720, "Fire Engine");

    Input::init(window->getHandle());

    Input::addKeyPressedCallback([](Input::Key key, Input::KeyEventType type) {
        SceneManager::getInstance()->getCurrentScene()->onKeyEvent(key, type);
    });

    // Then, graphics API
    Renderer::init((GLADloadproc)glfwGetProcAddress);
    Renderer::setClearColor();

    DebugUi::init(window->getHandle());  // TODO: Move into scene

    // Lastly, GPU buffers
    batchRenderer = std::make_shared<BatchRenderer>();

    textureStorage = std::make_shared<TextureStorage>();
}

Application::~Application() {
    SceneManager::disposeInstance();

    delete window;
}

void Application::init() {
}

void Application::run() {
    double frameTime = glfwGetTime();
    double plotCounter = 0;
    double debugFrameTime = 0;

    SceneManager::getInstance()->startScene();

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

        SceneManager::getInstance()->runSceneUpdate(currentFrameTime);
        /// End App Code

        SceneManager::getInstance()->runSceneRender();

        DebugUi::draw();  // TODO: Move into scene

        window->swapBuffers();

        frameTime = deltaTime;
    }

    DebugUi::dispose();  // TODO: Move into scene
}
