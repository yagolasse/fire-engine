#include "mesh.h"

#include <format>
#include <iostream>
#include <string>

#include <gtc/type_ptr.hpp>

#include "renderer.h"

Mesh::Mesh(
    std::vector<Vertex> vertexData,
    std::vector<unsigned int> indexData,
    std::vector<std::shared_ptr<Texture>> textureData
) : vertices(vertexData), textures(textureData), indices(indexData), transform(glm::mat4(1.0)) {
    vertexBuffer = std::make_unique<VertexBuffer>();
    vertexArrayBuffer = std::make_unique<VertexArrayBuffer>();
    elementArrayBuffer = std::make_unique<ElementArrayBuffer>();

    vertexArrayBuffer->bind();

    elementArrayBuffer->bind();
    elementArrayBuffer->bufferData(&indices[0], indices.size() * sizeof(unsigned int));

    vertexBuffer->bind();
    vertexBuffer->bufferData(&vertices[0], vertices.size() * sizeof(Vertex));

    vertexArrayBuffer->setupAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    vertexArrayBuffer->setupAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    vertexArrayBuffer->setupAttributePointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));

    vertexArrayBuffer->unbind();
}

Mesh::~Mesh() {
}

void Mesh::draw(std::shared_ptr<ShaderProgram> shader, std::shared_ptr<Camera> camera) {
    shader->bind();

    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection();

    shader->setMat4("model", glm::value_ptr(transform));
    shader->setMat4("view", glm::value_ptr(view));
    shader->setMat4("projection", glm::value_ptr(projection));

    for (int i = 0; i < textures.size(); i++) {
        Renderer::makeTextureActive(i);
        textures[i]->bind();
        shader->setInt(("texture" + std::to_string(i + 1)).c_str(), i);
    }

    vertexArrayBuffer->bind();
    Renderer::draw(indices.size());
    vertexArrayBuffer->unbind();
}

std::unique_ptr<Mesh> Mesh::createQuadMesh(std::shared_ptr<Texture> texture) {
    std::vector<Vertex> vertices = {
        Vertex { { -0.5f, -0.5f, 0.0f, }, { 0.0f, 0.0f, 0.0f, }, { 0.0f, 0.0f, } },
        Vertex { { 0.5f,  -0.5f, 0.0f, }, { 1.0f, 0.0f, 0.0f, }, { 1.0f, 0.0f, } },
        Vertex { { 0.5f,   0.5f, 0.0f, }, { 0.0f, 1.0f, 0.0f, }, { 1.0f, 1.0f, } },
        Vertex { { -0.5f,  0.5f, 0.0f, }, { 0.0f, 0.0f, 1.0f, }, { 0.0f, 1.0f, } },
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    auto ptr = std::make_unique<Mesh>(vertices, indices, { texture });
    return std::move();
}
