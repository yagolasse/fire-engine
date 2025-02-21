#include "mesh.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include "assertion.hpp"
#include "element_array_buffer.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "vertex_array_buffer.hpp"
#include "vertex_buffer.hpp"

Mesh::Mesh() {
    vertexBuffer = new VertexBuffer();
    vertexArrayBuffer = new VertexArrayBuffer();
    elementArrayBuffer = new ElementArrayBuffer();

    std::ifstream fragFileStream("resources/quad_fragment_shader.glsl");
    std::ifstream vertFileStream("resources/quad_vertex_shader.glsl");

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

    shader = new ShaderProgram(std::move(vertexShader), std::move(fragmentShader));
}

Mesh::~Mesh() {
    delete shader;
    delete elementArrayBuffer;
    delete vertexArrayBuffer;
    delete vertexBuffer;
}

void Mesh::init() {
    
}
