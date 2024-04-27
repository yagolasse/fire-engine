
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

    std::shared_ptr<ShaderProgram> shader = std::make_shared<ShaderProgram>(
        std::move(vertexShader), 
        std::move(fragmentShader)
    );

    Renderer::setClearColor();

    float aspectRatio = 1280.0f / 720.0f;

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3 { 0.0f, 0.0f, -3.0f }, glm::radians(75.0f), aspectRatio, 0.1f, 1000.0f
    );

    std::unique_ptr<Mesh> cubeMesh = Mesh::createCubeMesh({ 1.0f, 1.0f, 1.0f}, std::make_shared<Texture>("../resources/container-texture.jpg"));

    cubeMesh->translate({ 2.0f, 0.0f, 0.0f });
    cubeMesh->rotate(15.0f, { 1.0f, 0.0f, 1.0f });
    
    std::unique_ptr<Mesh> lightMesh = Mesh::createCubeMesh({ 1.0f, 1.0f, 1.0f}, std::make_shared<Texture>("../resources/container-texture.jpg"));

    lightMesh->scale(glm::vec3(0.3f));
    lightMesh->rotate(20.0f, { -1.0f, 0.0f, -1.0f });

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

        static glm::vec3 ambientLightColor = glm::vec3 { 1.0f, 1.0f, 1.0f };

        static glm::vec3 amgientLightPosition = glm::vec3 { 0.0f, 2.0f, 0.0f };
        static float strength = 1.0f;

        ImGui::SliderFloat("Ambient Light Strenght", &strength, 0.0f, 1.0f);
        ImGui::DragFloat3("Light Position", &amgientLightPosition[0]);
        ImGui::ColorPicker3("Ambient Light Color", &ambientLightColor[0]);

        shader->bind();

        shader->setFloat("ambientLightStrenght", strength);
        shader->setVec3("ambientLightPosition", amgientLightPosition);
        shader->setVec3("ambientLightColor", ambientLightColor);
        
        shader->setVec3("viewPosition", camera->getPosition());

        static float specularStrenght = 0.5f;
        ImGui::SliderFloat("Specular Strenght", &specularStrenght, 0.0f, 1.0f);

        shader->setFloat("specularStrenght", 0.5f);

        lightMesh->draw(shader, camera);
        cubeMesh->draw(shader, camera);

        DebugUi::draw();

        window.swapBuffers();

        time = glfwGetTime();
        frameTime = time - lastFrameTime;
        lastFrameTime = time;
    }

    DebugUi::dispose();

    return 0;
}
