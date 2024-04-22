#include "mesh.h"

#include <format>
#include <iostream>
#include <string>

#include "renderer.h"

Mesh::Mesh(std::vector<Vertex> vertexData, std::vector<Texture> textureData, std::vector<unsigned int> indexData)
    : vertices(vertexData), textures(textureData), indices(indexData) {
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
    vertexArrayBuffer->setupAttributePointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                             (void*)offsetof(Vertex, textureCoordinate));

    vertexArrayBuffer->unbind();
}

Mesh::~Mesh() {
}

void Mesh::draw(std::shared_ptr<ShaderProgram> shader) {
    shader->bind();

    // for (int i = 1; i < textures.size(); i++) {
        Renderer::makeTextureActive(1);
        textures[0].bind();
        shader->setInt(("texture" + std::to_string(1)).c_str(), 1);
    // }

    vertexArrayBuffer->bind();
    Renderer::draw(indices.size());
    vertexArrayBuffer->unbind();
}
