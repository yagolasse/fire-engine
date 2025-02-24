#include "mesh.hpp"

#include <string>
#include <vector>

#include "assertion.hpp"
#include "element_array_buffer.hpp"
#include "resource_loader.hpp"
#include "shader_program.hpp"
#include "renderer.hpp"
#include "vertex_array_buffer.hpp"
#include "vertex_buffer.hpp"

Mesh::Mesh() {
    vertexBuffer = new VertexBuffer();
    vertexArrayBuffer = new VertexArrayBuffer();
    elementArrayBuffer = new ElementArrayBuffer();

    std::string vertexString = ResourceLoader::readStringFromFile("resources/mesh_vertex_shader.glsl");
    std::string fragmentString = ResourceLoader::readStringFromFile("resources/mesh_fragment_shader.glsl");

    shader = new ShaderProgram();

    shader->linkShader(vertexString.c_str(), fragmentString.c_str());

    vertices = std::vector<MeshVertex>(3);
}

Mesh::~Mesh() {
    delete shader;
    delete elementArrayBuffer;
    delete vertexArrayBuffer;
    delete vertexBuffer;
}

void Mesh::init() {
    std::vector<unsigned int> indices(3);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    vertexArrayBuffer->bind();

    elementArrayBuffer->bind();
    elementArrayBuffer->bufferData(&indices[0], indices.size() * sizeof(unsigned int));

    vertexBuffer->bind();
    vertexBuffer->bufferData(nullptr, 3 * sizeof(MeshVertex));

    vertexArrayBuffer->setupFloatAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)0);

    vertexBuffer->unbind();

    elementArrayBuffer->unbind();

    vertexArrayBuffer->unbind();
}

void Mesh::draw() {
    vertices[0] = MeshVertex{{0.0f, 0.5f, 0.0f}};
    vertices[1] = MeshVertex{{-0.5f, -0.5f, 0.0f}};
    vertices[2] = MeshVertex{{0.5f, -0.5f, 0.0f}};

    shader->bind();

    vertexArrayBuffer->bind();

    elementArrayBuffer->bind();

    vertexBuffer->bind();
    vertexBuffer->bufferSubData(&vertices[0], 0, 3 * sizeof(MeshVertex));

    Renderer::getInstance()->draw(3);

    vertexBuffer->unbind();

    elementArrayBuffer->unbind();

    vertexArrayBuffer->unbind();
    
    shader->unbind();
}
