#include "batch_renderer.h"

#include "quad_vertex.h"

BatchRenderer::BatchRenderer() {
    vertexBuffer = std::make_unique<VertexBuffer>();
    vertexArrayBuffer = std::make_unique<VertexArrayBuffer>();
    elementArrayBuffer = std::make_unique<ElementArrayBuffer>();

    vertexArrayBuffer->bind();

    vertexArrayBuffer->setupAttributePointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Quad), (void*)0);
    vertexArrayBuffer->setupAttributePointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Quad), (void*)offsetof(Quad, color));

    vertexArrayBuffer->unbind();
}

void BatchRenderer::pushQuad(Quad quad) {
    quads.push_back(quad);
}
