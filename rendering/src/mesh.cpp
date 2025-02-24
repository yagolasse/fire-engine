#include "mesh.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "assertion.hpp"
#include "element_array_buffer.hpp"
#include "resource_loader.hpp"
#include "shader_program.hpp"
#include "vertex_array_buffer.hpp"
#include "vertex_buffer.hpp"

Mesh::Mesh() {
    vertexBuffer = new VertexBuffer();
    vertexArrayBuffer = new VertexArrayBuffer();
    elementArrayBuffer = new ElementArrayBuffer();

    std::string vertexString = ResourceLoader::readStringFromFile("resources/quad_vertex_shader.glsl");
    std::string fragmentString = ResourceLoader::readStringFromFile("resources/quad_fragment_shader.glsl");

    shader = new ShaderProgram();

    shader->linkShader(vertexString.c_str(), fragmentString.c_str());
}

Mesh::~Mesh() {
    delete shader;
    delete elementArrayBuffer;
    delete vertexArrayBuffer;
    delete vertexBuffer;
}

void Mesh::init() {
}
