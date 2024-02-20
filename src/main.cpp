#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <fstream>
#include <memory>
#include <sstream>

#include "assertion.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"
#include "window.h"

int main(int argc, char* argv[]) {
    Window window(1280, 720, "Hello Window");

    Renderer::init();

    std::ifstream fragFileStream("../resources/frag.glsl");
    std::ifstream vertFileStream("../resources/vert.glsl");

    ASSERT_MSG(!fragFileStream.fail(), "Failed to open fragment shader");
    ASSERT_MSG(!vertFileStream.fail(), "Failed to open fragment shader");

    std::stringstream fragStringBuffer;
    std::stringstream vertStringBuffer;

    fragStringBuffer << fragFileStream.rdbuf();
    vertStringBuffer << vertFileStream.rdbuf();

    auto vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, vertStringBuffer.str().c_str());
    auto fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, fragStringBuffer.str().c_str());

    fragFileStream.close();
    vertFileStream.close();

    auto shader = std::make_unique<ShaderProgram>(std::move(vertexShader), std::move(fragmentShader));

    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    VertexArrayBuffer vertexArrayBuffer;

    vertexArrayBuffer.bind();

    VertexBuffer vertexBuffer;

    vertexBuffer.bind();

    vertexBuffer.bufferData(vertices, sizeof(vertices));

    vertexArrayBuffer.setupAttributePointer(0, 3);

    Renderer::setClearColor();

    shader->bind();

    while (!window.shouldClose()) {
        Renderer::clear();

        Renderer::draw();

        window.pollEvents();

        window.swapBuffers();
    }

    return 0;
}
