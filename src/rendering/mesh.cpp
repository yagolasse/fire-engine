#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertexData, std::vector<unsigned int> indexData) {
    vertexBuffer = std::make_unique<VertexBuffer>();
    vertexArrayBuffer = std::make_unique<VertexArrayBuffer>();
    elementArrayBuffer = std::make_unique<ElementArrayBuffer>();

    vertexArrayBuffer->bind();
    vertexBuffer->bind();

    vertexBuffer->bufferData(&vertices[0], vertices.size() * sizeof(Vertex));

    elementArrayBuffer->bind();
    elementArrayBuffer->bufferData(&indices[0], indices.size() * sizeof(unsigned int));

    vertexArrayBuffer->setupAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    vertexArrayBuffer->setupAttributePointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));
}
