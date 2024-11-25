#include "application.h"

#include <imgui.h>

#include <iostream>

#include "debug_ui.h"
#include "renderer.h"
#include "script.h"
#include "sprite_sheet.h"
#include "texture_storage.h"
#include "texture_region.h"
#include "texture.h"
#include "texture_data.h"
#include "sprite.h"

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
    Script script;

    script.start();

    std::shared_ptr<OrthographicCamera> camera =
        std::make_shared<OrthographicCamera>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 1000.0f);

    Sprite sprite(batchRenderer, textureStorage->loadTexture("../resources/simpleSpace_tilesheet.png"), 64, 64);
    
    double frameTime = glfwGetTime();

    while (!window->shouldClose()) {
        double deltaTime = glfwGetTime();

        window->pollEvents();

        /// App Code

        DebugUi::beginFrame();  // TODO: Move into scene

        script.update(deltaTime - frameTime);

        textureStorage->bind();
        
        sprite.update(deltaTime - frameTime);

        ImGui::Text("%.2f ms", (deltaTime - frameTime) * 1000.0);  // TODO: Move into scene

        /// End App Code

        batchRenderer->draw(camera);

        DebugUi::draw();  // TODO: Move into scene

        window->swapBuffers();

        frameTime = deltaTime;

        // exit(0);
    }

    DebugUi::dispose();  // TODO: Move into scene
}
