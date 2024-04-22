
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

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,  // Left bottom
    //     0.5f,  -0.5f, 0.0f,  // Right bottom
    //     0.5f,  0.5f,  0.0f,  // Top Right
    //     -0.5f, 0.5f,  0.0f,  // Top Left
    // };

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

    // unsigned int indices[36];

    // int index = 0;
    
    // for (int i = 0; i < 36; i += 6) {
    //     indices[0 + i] = 0 + index;
    //     indices[1 + i] = 1 + index;
    //     indices[2 + i] = 2 + index;
    //     indices[3 + i] = 2 + index;
    //     indices[4 + i] = 3 + index;
    //     indices[5 + i] = 0 + index;
    //     index += 4;
    // }

    // float texCoords[] = {
    //     0.0f, 0.0f,  // lower-left corner
    //     1.0f, 0.0f,  // lower-right corner
    //     1.0f, 1.0f,  // top-right corner
    //     0.0f, 1.0f,  // top-left corner
    // };
    
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

    // VertexArrayBuffer vertexArrayBuffer;

    // vertexArrayBuffer.bind();

    // ElementArrayBuffer elementArrayBuffer;

    // elementArrayBuffer.bind();

    // elementArrayBuffer.bufferData(&indices[0], indices.size() * sizeof(unsigned int));

    // VertexBuffer vertexBuffer;

    // vertexBuffer.bind();

    // vertexBuffer.bufferData(&vertices[0], vertices.size() * sizeof(Vertex));

    // vertexArrayBuffer.setupAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertexArrayBuffer.setupAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    // vertexArrayBuffer.setupAttributePointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));
    
    // vertexArrayBuffer.unbind();

    // VertexBuffer colorVertexBuffer;

    // colorVertexBuffer.bind();

    // colorVertexBuffer.bufferData(colors, sizeof(colors));

    // vertexArrayBuffer.setupAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

    // VertexBuffer textureCoordinateBuffer;

    // textureCoordinateBuffer.bind();

    // textureCoordinateBuffer.bufferData(texCoords, sizeof(texCoords));

    // vertexArrayBuffer.setupAttributePointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

    Texture containerTexture("../resources/container-texture.jpg");

    Texture smileTexture("../resources/awesomeface.png");

    std::vector<Texture> textures = {
        smileTexture, containerTexture, 
    };

    Renderer::setClearColor();

    Mesh mesh(vertices, textures, indices);

    glm::mat4 model(1.0f);
    // model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(70.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    while (!window.shouldClose()) {
        window.pollEvents();

        DebugUi::beginFrame();

        Renderer::clear();

        // shader->bind();

        // smileTexture.bind();
        // containerTexture.bind();

        // shader.setInt("texture1", containerTexture.getIndex());
        // shader.setInt("texture2", smileTexture.getIndex());

        // const float radius = 10.0f;
        // float cameraZ = glm::cos(glfwGetTime()) * radius;
        // float cameraX = glm::sin(glfwGetTime()) * radius;

        // camera.setPosition({cameraX, 0.0f, cameraZ});

        glm::mat4 view = camera.getView();

        // shader->setMat4("model", glm::value_ptr(model));
        // shader->setMat4("view", glm::value_ptr(view));
        // shader->setMat4("projection", glm::value_ptr(projection));

        // vertexArrayBuffer.bind();

        // Renderer::draw(indices.size());

        // vertexArrayBuffer.unbind();

        mesh.draw(shader);

        DebugUi::draw();

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
