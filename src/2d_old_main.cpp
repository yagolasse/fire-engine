
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
#include "camera.h"
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

    std::ifstream fragFileStream("../resources/frag.glsl");
    std::ifstream vertFileStream("../resources/vert.glsl");

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

    std::shared_ptr<Camera> camera =
        std::make_shared<Camera>(glm::vec3{0.0f, 0.0f, -3.0f}, -0.5f, 0.5, -0.5f, 0.5f, 0.01f, 1000.0f);

    double time = glfwGetTime();
    double lastFrameTime = time;
    double frameTime = 0;

    double deltaTime = 0;
    double slowFrameTime = 0;

    Quad quad{
        {
            glm::vec2{
                0.0f,
                0.0f,
            },
            glm::vec2{1.0f, 1.0f}, 0.0f
        },
        glm::vec4(1.0f)
    };

    while (!window.shouldClose()) {
        window.pollEvents();

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

        batchRenderer.pushQuad(quad);

        shader->bind();
        // shader->setMat4("view", &camera->getView()[0][0]);
        // shader->setMat4("projection", &camera->getProjection()[0][0]);

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
