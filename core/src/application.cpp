#include "application.hpp"

#include <imgui.h>

#include <chrono>
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
    Renderer::getInstance()->init((LoadProcedure)glfwGetProcAddress);
    Renderer::getInstance()->setClearColor();

    DebugUi::init(window->getHandle());

    BatchRenderer::getInstance()->init();
    TextureStorage::getInstance()->init();
}

Application::~Application() {
    SceneManager::disposeInstance();
    BatchRenderer::disposeInstance();
    TextureStorage::disposeInstance();
    Renderer::disposeInstance();

    delete window;
}

void Application::init() {
}

void Application::run() {
    SceneManager::getInstance()->startScene();

    double previousTime = glfwGetTime();
    double accumulator = 0.0;
    const double fixedTimeStep = 1.0 / 60.0; // Target update rate: 60 updates per second

    while (!window->shouldClose()) {

        DebugUi::beginFrame();  // TODO: Move into scene
        
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        // Accumulate the elapsed time
        accumulator += deltaTime;

        window->pollEvents();

        while (accumulator >= fixedTimeStep) {
            auto before = std::chrono::high_resolution_clock::now();
            SceneManager::getInstance()->runSceneUpdate(fixedTimeStep);
            accumulator -= fixedTimeStep;
            std::cout << "Scene update " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - before).count() << std::endl;
        }

        ImGui::Text("%.2f ms", deltaTime * 1000.0); 
        ImGui::Text("%.0f FPS", 1.0 / deltaTime); 
        
        SceneManager::getInstance()->runSceneRender();

        DebugUi::draw();

        window->swapBuffers();
    }

    DebugUi::dispose();
}
