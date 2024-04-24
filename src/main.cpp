
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <imgui.h>

#include "assertion.h"
#include "element_array_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"
#include "window.h"
#include "camera.h"
#include "debug_ui.h"
#include "vertex.h"
#include "mesh.h"
#include "batch_renderer.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]) {
    
    Window window(1280, 720, "Hello Window");

    Renderer::init((GLADloadproc) glfwGetProcAddress);

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

    std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>(
        std::move(vertexShader), 
        std::move(fragmentShader)
    );

    Renderer::setClearColor();

    float aspectRatio = 720.0f / 1280.f;

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        // glm::vec3 { 0.0f, 0.0f, 0.0f }, -1.0, 1.0f, -aspectRatio, aspectRatio, -1.0, 1.0
        glm::vec3 { 0.0f, 0.0f, 0.0f }, 0, 720, 0, 1280, -1.0, 1.0
    );

    Quad quad {
        Transform {
            glm::vec2 { 100, 100 },
            glm::vec2 { 640, 360 },
        },
        glm::vec4(1.0f)
    };

    BatchRenderer batchRenderer;
    
    batchRenderer.pushQuad(quad);

    double time = glfwGetTime();
    double lastFrameTime = time;
    double frameTime = 0;

    double deltaTime = 0;
    double slowFrameTime = 0;

    while (!window.shouldClose()) {

        window.pollEvents();

        DebugUi::beginFrame();

        Renderer::clear();

        if(deltaTime > 1) {
            slowFrameTime = frameTime;
            deltaTime = 0;
        } else {
            deltaTime += frameTime;
        }

        ImGui::Text("%d FPS", (int)(1.0 / slowFrameTime));
        ImGui::Text("%.2f ms", slowFrameTime * 1000.0);

        shader->bind();

        glm::mat4 view = camera->getView();
        glm::mat4 projection = camera->getProjection();

        shader->setMat4("view", glm::value_ptr(view));
        shader->setMat4("projection", glm::value_ptr(projection));

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
