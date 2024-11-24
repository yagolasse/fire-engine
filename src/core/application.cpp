#include "application.h"

#include <imgui.h>

#include <iostream>

#include "debug_ui.h"
#include "renderer.h"
#include "script.h"
#include "sprite_sheet.h"
#include "texture_storage.h"
#include "texture.h"
#include "texture_data.h"

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

    // SpriteSheet spriteSheet(assetLoader->loadTexture("simpleSpace_tilesheet.png"), 64, 64);

    // Texture texture("../resources/awesomeface.png");
    TextureStorage textureStorage;
    TextureData texture = textureStorage.loadTexture("../resources/simpleSpace_tilesheet.png");

    TextureData otherTexture = textureStorage.loadTexture("../resources/awesomeface.png");
    double frameTime = glfwGetTime();

    int spriteIndex = 0;
    double accumulator = 0;
    float rotation = 0;

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

        rotation += 0.04;
        textureStorage.bind();
        // texture.bind();
        // spriteSheet.bindTexture();

        // for (int i = 0; i < 30; i++) {
        //     for (int j = 0; j < 30; j++) {
        //         Quad quad1{
        //             {
        //                 glm::vec2{30.0f, 30.0f}, // Scale
        //                 glm::vec2{j * 20.0f + 10, i * 20.0f + 10}, // Position
        //                 0.0f // Rotation
        //             },
        //             glm::vec4(glm::vec3((float)i/800.0f , (float)j/200.0f, 0.5f), 1.0f) ,// Color,
        //         };
        //         batchRenderer->pushQuad(quad1);
        //     }
        // }

        // Quad quad1{
        //     {
        //         glm::vec2{spriteSheet.getSpriteWidth(), spriteSheet.getSpriteHeight()},  // Scale
        //         glm::vec2{640.0f, 360.0f},                                               // Position
        //         rotation                                                                    // Rotation
        //     },
        //     glm::vec4(1.0f),  // Color
        //     spriteSheet.getUVMappingForRegion(spriteIndex),
        //     0,
        // };

        // Quad quad1{
        //     {
        //         glm::vec2{texture.getWidth(), texture.getHeight()},  // Scale
        //         glm::vec2{640.0f, 360.0f},                                               // Position
        //         rotation                                                                    // Rotation
        //     },
        //     glm::vec4(1.0f),  // Color
        //     std::array<glm::vec2, 4>{
        //         glm::vec2{0.0f, 0.0f},
        //         glm::vec2{1.0f, 0.0f},
        //         glm::vec2{1.0f, 1.0f},
        //         glm::vec2{0.0f, 1.0f},
        //     },
        // };


        Quad quad1{
            {
                glm::vec2{texture.width, texture.height},  // Scale
                glm::vec2{640.0f, 360.0f},                                               // Position
                rotation                                                                    // Rotation
            },
            glm::vec4(1.0f),  // Color
            std::array<glm::vec2, 4>{
                glm::vec2{0.0f, 0.0f},
                glm::vec2{texture.maxUV.x, 0.0f},
                glm::vec2{texture.maxUV.x, texture.maxUV.y},
                glm::vec2{0.0f, texture.maxUV.y},
            },
            texture.depth,
        };
        batchRenderer->pushQuad(quad1);

        Quad quad2{
            {
                glm::vec2{otherTexture.width, otherTexture.height},  // Scale
                glm::vec2{1280.0f, 720.0f},                                               // Position
                0.0f                                                                    // Rotation
            },
            glm::vec4(1.0f),  // Color
            std::array<glm::vec2, 4>{
                glm::vec2{0.0f, 0.0f},
                glm::vec2{otherTexture.maxUV.x, 0.0f},
                glm::vec2{otherTexture.maxUV.x, otherTexture.maxUV.y},
                glm::vec2{0.0f, otherTexture.maxUV.y},
            },
            otherTexture.depth,
        };

        batchRenderer->pushQuad(quad2);

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
