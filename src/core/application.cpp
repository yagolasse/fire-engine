#include "application.h"

#include <imgui.h>

#include <iostream>

#include "debug_ui.h"
#include "renderer.h"
#include "script.h"
#include "sprite_sheet.h"

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
    batchRenderer = std::make_unique<BatchRenderer>();

    assetLoader = std::make_unique<AssetLoader>();
}

void Application::run() {
    Script script;

    script.start();

    std::shared_ptr<OrthographicCamera> camera =
        std::make_shared<OrthographicCamera>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 1000.0f);

    SpriteSheet spriteSheet(assetLoader->loadTexture("simpleSpace_tilesheet.png"), 64, 64);

    double frameTime = glfwGetTime();

    int spriteIndex = 0;
    double accumulator = 0;

    while (!window->shouldClose()) {
        double deltaTime = glfwGetTime();

        window->pollEvents();

        /// App Code

        DebugUi::beginFrame();  // TODO: Move into scene

        script.update(deltaTime - frameTime);

        accumulator += deltaTime - frameTime;

        if (accumulator > 1) {
            accumulator = 0;
            std::cout << spriteIndex << std::endl;
            spriteIndex++;
            if (spriteIndex == 8 * 6) {
                spriteIndex = 0;
            }
        }

        Renderer::makeTextureActive(1);
        spriteSheet.bindTexture();

        // for (int i = 0; i < 30; i++) {
        //     for (int j = 0; j < 30; j++) {
        //         Quad quad1{
        //             {
        //                 glm::vec2{30.0f, 30.0f}, // Scale
        //                 glm::vec2{j * 20.0f + 10, i * 20.0f + 10}, // Position
        //                 0.0f // Rotation
        //             },
        //             glm::vec4(glm::vec3((float)i/800.0f , (float)j/200.0f, 0.5f), 1.0f) // Color
        //         };
        //         batchRenderer->pushQuad(quad1);
        //     }
        // }

        Quad quad1{
            {
                glm::vec2{spriteSheet.getSpriteWidth(), spriteSheet.getSpriteHeight()},  // Scale
                glm::vec2{640.0f, 360.0f},                                               // Position
                0.0f                                                                     // Rotation
            },
            glm::vec4(1.0f),  // Color
            spriteSheet.getUVMappingForRegion(spriteIndex),
        };

        batchRenderer->pushQuad(quad1);

        ImGui::Text("%.2f ms", (deltaTime - frameTime) * 1000.0);  // TODO: Move into scene

        /// End App Code

        batchRenderer->draw(camera);

        DebugUi::draw();  // TODO: Move into scene

        window->swapBuffers();

        frameTime = deltaTime;
    }

    DebugUi::dispose();  // TODO: Move into scene
}
