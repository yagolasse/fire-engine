
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

    Mesh mesh(vertices, indices, textures);

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3 { 0.0f, 0.0f, -3.0f }, 
        glm::radians(70.0f), 
        1280.0f / 720.0f, 
        0.1f, 
        100.0f
    );

    while (!window.shouldClose()) {
        window.pollEvents();

        DebugUi::beginFrame();

        Renderer::clear();

        mesh.draw(shader, camera);

        DebugUi::draw();

        // TODO: Remove error handling
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            std::cerr << err << std::endl;
        }

        window.swapBuffers();
    }

    DebugUi::dispose();

    return 0;
}
