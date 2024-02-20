#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <memory>
#include <fstream>
#include <sstream>

#include "core/window.h"
#include "rendering/renderer.h"
#include "rendering/shader.h"
#include "rendering/shader_program.h"
#include "rendering/vertex_buffer.h"

int main(int argc, char* argv[]) {
    Window window(1280, 720, "Hello Window");

    Renderer::init();

    std::ifstream fragFileStream("/Users/yagolasse/Documents/Projects/fire-engine/resources/frag.glsl");
    std::ifstream vertFileStream("/Users/yagolasse/Documents/Projects/fire-engine/resources/vert.glsl");

    std::stringstream fragStringBuffer;
    std::stringstream vertStringBuffer;

    fragStringBuffer << fragFileStream.rdbuf();
    vertStringBuffer << vertFileStream.rdbuf();

    auto vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, vertStringBuffer.str().c_str());
    auto fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, fragStringBuffer.str().c_str());

    fragFileStream.close();
    vertFileStream.close();

    auto shader = std::make_unique<ShaderProgram>(std::move(vertexShader), std::move(fragmentShader));

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f
    };

    VertexBuffer vertexBuffer;

    vertexBuffer.bind();

    vertexBuffer.bufferData(vertices, sizeof(vertices));

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
