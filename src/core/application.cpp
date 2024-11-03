#include "application.h"

#include <imgui.h>

#include "debug_ui.h"
#include "renderer.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Application::Application() {
    // First, window context
    window = std::make_unique<Window>(1280, 720, "Fire Engine");

    // Then, graphics API
    Renderer::init((GLADloadproc)glfwGetProcAddress);
    Renderer::setClearColor();

    DebugUi::init(window->getHandle()); // TODO: Move into scene

    // Lastly, GPU buffers
    batchRenderer = std::make_unique<BatchRenderer>();
}

void Application::run() {

    std::shared_ptr<OrthographicCamera> camera =
        std::make_shared<OrthographicCamera>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.0f, 1280.0f, 720.0f, 0.0f, 0.01f, 1000.0f);
        
    double frameTime = glfwGetTime();

    while(!window->shouldClose()) {
        double deltaTime = glfwGetTime();

        window->pollEvents();

        /// App Code
        
        DebugUi::beginFrame(); // TODO: Move into scene

        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                Quad quad1{
                    {
                        glm::vec2{5.0f, 5.0f}, // Scale
                        glm::vec2{j * 8.0f + 10, i * 8.0f + 10}, // Position
                        0.0f // Rotation
                    },
                    glm::vec4(glm::vec3((float)i/800.0f , (float)j/200.0f, 0.5f), 1.0f) // Color
                };
                batchRenderer->pushQuad(quad1);
            }
        }

        ImGui::Text("%.2f ms", (deltaTime - frameTime) * 1000.0); // TODO: Move into scene

        /// End App Code
        
        batchRenderer->draw(camera);

        DebugUi::draw(); // TODO: Move into scene

        window->swapBuffers();

        frameTime = deltaTime;
    }

    DebugUi::dispose(); // TODO: Move into scene
}
