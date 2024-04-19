#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <fstream>
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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Left bottom
        0.5f,  -0.5f, 0.0f,  // Right bottom
        0.5f,  0.5f,  0.0f,  // Top Right
        -0.5f, 0.5f,  0.0f,  // Top Left
    };

    float colors[] = {
        0.0f, 0.0f, 0.0f,  // Left bottom
        1.0f, 0.0f, 0.0f,  // Right bottom
        0.0f, 1.0f, 0.0f,  // Top Right
        0.0f, 0.0f, 1.0f,  // Top Left
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
    };

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner
        1.0f, 0.0f,  // lower-right corner
        1.0f, 1.0f,  // top-right corner
        0.0f, 1.0f,  // top-left corner
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

    Texture smileTexture("../resources/awesomeface.png");

    Texture containerTexture("../resources/container-texture.jpg");

    Renderer::setClearColor();

    while (!window.shouldClose()) {
        shader.bind();

        smileTexture.bind();
        containerTexture.bind();
        
        shader.setInt("texture1", 0);
        shader.setInt("texture2", 1);

        Renderer::clear();

        Renderer::draw();

        window.pollEvents();

        window.swapBuffers();
    }

    return 0;
}
