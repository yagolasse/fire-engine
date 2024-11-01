
#include <imgui.h>
#include <stdio.h>

#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "assertion.h"
#include "batch_renderer.h"
#include "orthographic_camera.h"
#include "debug_ui.h"
#include "element_array_buffer.h"
#include "mesh.h"
#include "quad.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"
#include "window.h"


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]) {
    Window window(1280, 720, "Hello Window");

    Renderer::init((GLADloadproc)glfwGetProcAddress);

    DebugUi::init(window.getHandle());

    std::ifstream fragFileStream("../resources/quad_fragment_shader.glsl");
    std::ifstream vertFileStream("../resources/quad_vertex_shader.glsl");

    ASSERT_MSG(!fragFileStream.fail(), "Failed to open fragment shader");
    ASSERT_MSG(!vertFileStream.fail(), "Failed to open vertex shader");

    std::stringstream fragStringBuffer;
    std::stringstream vertStringBuffer;

    fragStringBuffer << fragFileStream.rdbuf();
    vertStringBuffer << vertFileStream.rdbuf();

    auto vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, vertStringBuffer.str().c_str());
    auto fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, fragStringBuffer.str().c_str());

    fragFileStream.close();
    vertFileStream.close();

    std::shared_ptr<ShaderProgram> shader =
        std::make_shared<ShaderProgram>(std::move(vertexShader), std::move(fragmentShader));

    Renderer::setClearColor();

    BatchRenderer batchRenderer;

    float aspectRatio = 1280.0f / 720.0f;

    std::shared_ptr<OrthographicCamera> camera =
        std::make_shared<OrthographicCamera>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.0f, 1280.0f, 720.0f, 0.0f, 0.01f, 1000.0f);

    double time = glfwGetTime();
    double lastFrameTime = time;
    double frameTime = 0;

    double deltaTime = 0;
    double slowFrameTime = 0;

    Quad quad{
        {
            glm::vec2{100.0f, 100.0f}, // Scale
            glm::vec2{50.0f, 50.0f}, // Position
            0.0f // Rotation
        },
        glm::vec4(1.0f) // Color
    };

    float rotation = 0;

    while (!window.shouldClose()) {
        window.pollEvents();

        // rotation += deltaTime;

        DebugUi::beginFrame();

        Renderer::clear();

        if (deltaTime > 1) {
            slowFrameTime = frameTime;
            deltaTime = 0;
        } else {
            deltaTime += frameTime;
        }

        ImGui::Text("%d FPS", (int)(1.0 / slowFrameTime));
        ImGui::Text("%.2f ms", slowFrameTime * 1000.0);

        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 200; j++) {
                Quad quad1{
                    {
                        glm::vec2{5.0f, 5.0f}, // Scale
                        glm::vec2{j * 8.0f + 10, i * 8.0f + 10}, // Position
                        rotation // Rotation
                    },
                    glm::vec4(glm::vec3((float)i/800.0f , (float)j/200.0f, 0.5f), 1.0f) // Color
                };
                batchRenderer.pushQuad(quad1);
            }
        }

        shader->bind();
        shader->setMat4("view", glm::value_ptr(camera->getView()));
        shader->setMat4("projection", glm::value_ptr(camera->getProjection()));

        batchRenderer.draw();

        DebugUi::draw();

        window.swapBuffers();

        time = glfwGetTime();
        frameTime = time - lastFrameTime;
        lastFrameTime = time;
    }

    DebugUi::dispose();

    return 0;
}
