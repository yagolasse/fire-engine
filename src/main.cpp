#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <memory>
#include <sstream>

#include "assertion.h"
#include "element_array_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"
#include "window.h"

int main(int argc, char* argv[]) {
    
    Window window(1280, 720, "Hello Window");

    Renderer::init();

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

    ShaderProgram shader(std::move(vertexShader), std::move(fragmentShader));

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,  // Left bottom
    //     0.5f,  -0.5f, 0.0f,  // Right bottom
    //     0.5f,  0.5f,  0.0f,  // Top Right
    //     -0.5f, 0.5f,  0.0f,  // Top Left
    // };

    float vertices[] = {
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

    unsigned int indices[36];

    int index = 0;
    
    for (int i = 0; i < 36; i += 6) {
        indices[0 + i] = 0 + index;
        indices[1 + i] = 1 + index;
        indices[2 + i] = 2 + index;
        indices[3 + i] = 2 + index;
        indices[4 + i] = 3 + index;
        indices[5 + i] = 0 + index;
        index += 4;
    }

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

    VertexArrayBuffer vertexArrayBuffer;

    vertexArrayBuffer.bind();

    ElementArrayBuffer elementArrayBuffer;

    elementArrayBuffer.bind();

    elementArrayBuffer.bufferData(indices, sizeof(indices));

    VertexBuffer vertexBuffer;

    vertexBuffer.bind();

    vertexBuffer.bufferData(vertices, sizeof(vertices));

    vertexArrayBuffer.setupAttributePointer(0, 3);

    VertexBuffer colorVertexBuffer;

    colorVertexBuffer.bind();

    colorVertexBuffer.bufferData(colors, sizeof(colors));

    vertexArrayBuffer.setupAttributePointer(1, 3);

    VertexBuffer textureCoordinateBuffer;

    textureCoordinateBuffer.bind();

    textureCoordinateBuffer.bufferData(texCoords, sizeof(texCoords));

    vertexArrayBuffer.setupAttributePointer(2, 2);

    Texture containerTexture("../resources/container-texture.jpg");

    Texture smileTexture("../resources/awesomeface.png");

    Renderer::setClearColor();

    glm::mat4 model(1.0f);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(70.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    while (!window.shouldClose()) {
        shader.bind();

        smileTexture.bind();
        containerTexture.bind();

        shader.setInt("texture1", 0);
        shader.setInt("texture2", 1);

        model = glm::rotate(model, glm::radians(1.0f) * 0.016f, glm::vec3(1.0f, 1.0f, 0.0f));

        shader.setMat4("model", glm::value_ptr(model));
        shader.setMat4("view", glm::value_ptr(view));
        shader.setMat4("projection", glm::value_ptr(projection));

        Renderer::clear();

        Renderer::draw();

        window.pollEvents();

        window.swapBuffers();
    }

    return 0;
}
