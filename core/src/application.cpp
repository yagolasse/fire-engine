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
    Renderer::getInstance()->init((LoadProcedure)glfwGetProcAddress);
    Renderer::getInstance()->setClearColor();

    DebugUi::init(window->getHandle());  // TODO: Move into scene

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
            SceneManager::getInstance()->runSceneUpdate(fixedTimeStep);
            accumulator -= fixedTimeStep;
        }

        ImGui::Text("%.2f ms", deltaTime * 1000.0);  // TODO: Move into scene

        /// End App Code

        SceneManager::getInstance()->runSceneRender();

        DebugUi::draw();  // TODO: Move into scene

        window->swapBuffers();
    }

    DebugUi::dispose();  // TODO: Move into scene
}

/*
// The amount of time we want to simulate each step, in milliseconds
// (written as implicit frame-rate)
timeDelta = 1000/30
timeAccumulator = 0
while ( game should run )
{
  timeSimulatedThisIteration = 0
  startTime = currentTime()

  while ( timeAccumulator >= timeDelta )
  {
    stepGameState( timeDelta )
    timeAccumulator -= timeDelta
    timeSimulatedThisIteration += timeDelta
  }

  stepAnimation( timeSimulatedThisIteration )

  renderFrame() // OpenGL frame drawing code goes here

  handleUserInput()

  timeAccumulator += currentTime() - startTime 
}
  */
