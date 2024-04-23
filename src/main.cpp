
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

    float old_vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f,

        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
    };

    float colors[] = {
        0.0f, 0.0f, 0.0f,  // Left bottom
        1.0f, 0.0f, 0.0f,  // Right bottom
        0.0f, 1.0f, 0.0f,  // Top Right
        0.0f, 0.0f, 1.0f,  // Top Left
    };

    float texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };

    std::vector<Vertex> vertices = {
        Vertex { { -0.5f, -0.5f, 0.0f, }, { 0.0f, 0.0f, 0.0f, }, { 0.0f, 0.0f, } },
        Vertex { { 0.5f,  -0.5f, 0.0f, }, { 1.0f, 0.0f, 0.0f, }, { 1.0f, 0.0f, } },
        Vertex { { 0.5f,   0.5f, 0.0f, }, { 0.0f, 1.0f, 0.0f, }, { 1.0f, 1.0f, } },
        Vertex { { -0.5f,  0.5f, 0.0f, }, { 0.0f, 0.0f, 1.0f, }, { 0.0f, 1.0f, } },
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    std::vector<std::shared_ptr<Texture>> textures = { 
        std::make_shared<Texture>("../resources/container-texture.jpg"),
        std::make_shared<Texture>("../resources/awesomeface.png"),
    };

    Renderer::setClearColor();

    // Mesh mesh(vertices, indices, textures);

    std::vector<std::unique_ptr<Mesh>> meshes = {};

    int count = 1;
    int perAxis = 10;

    for (int i = 0; i < count; i++) {
        meshes.push_back(Mesh::createCubeMesh({ 1.0f, 1.0f, 1.0f }, std::make_shared<Texture>("../resources/container-texture.jpg")));
    }

    for (int i = 0; i < count; i++) {
        int x = i / (perAxis * perAxis) %perAxis;
        int y = i / (perAxis) % perAxis;
        int z = i % perAxis;

        std::cout << x << ", " << y << ", " << z << std::endl;

        meshes[i]->translate({ x, y, z });
    }

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3 { 0.0f, 0.0f, -1.0f },  0, 1280, 720, 0, 0.1, 1000
    );

    double time = glfwGetTime();
    double lastFrameTime = time;
    double frameTime = 0;

    double deltaTime = 0;
    double slowFrameTime = 0;

    while (!window.shouldClose()) {

        window.pollEvents();

        // for (int i = 0; i < count; i++) {
        //     meshes[i]->rotate(1.5 * frameTime, { 0.0f, 1.0f, 1.0f });
        // }

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

        // camera->setPosition(camera->getPosition() + glm::vec3 { 0.0f, 0.5f * frameTime, 0.0f });

        for (int i = 0; i < count; i++) {
            meshes[i]->draw(shader, camera);
        }

        DebugUi::draw();

        // TODO: Remove error handling
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            std::cerr << err << std::endl;
        }

        window.swapBuffers();

        time = glfwGetTime();
        frameTime = time - lastFrameTime;
        lastFrameTime = time;
    }

    DebugUi::dispose();

    return 0;
}
