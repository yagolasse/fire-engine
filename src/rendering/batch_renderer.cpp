#include "batch_renderer.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>

#include "error.h"
#include "quad.h"
#include "renderer.h"

const int indexPerQuad = 6;
const int vertexPerQuad = 4;
const int maxQuadsPerDraw = 100;
const int maxIndex = indexPerQuad * maxQuadsPerDraw;
const int maxVertex = vertexPerQuad * maxQuadsPerDraw;

BatchRenderer::BatchRenderer() {
    vertexBuffer = std::make_unique<VertexBuffer>();
    vertexArrayBuffer = std::make_unique<VertexArrayBuffer>();
    elementArrayBuffer = std::make_unique<ElementArrayBuffer>();

    std::array<unsigned int, maxIndex> indices;

    int index = 0;

    for (int i = 0; i < maxIndex; i += indexPerQuad) {
        indices[0 + i] = 0 + index;
        indices[1 + i] = 1 + index;
        indices[2 + i] = 2 + index;
        indices[3 + i] = 2 + index;
        indices[4 + i] = 3 + index;
        indices[5 + i] = 0 + index;
        index += 4;
    }

    vertexArrayBuffer->bind();

    elementArrayBuffer->bind();
    elementArrayBuffer->bufferData(&indices[0], indices.size() * sizeof(unsigned int));

    vertexBuffer->bind();
    vertexBuffer->bufferData(nullptr, maxVertex * sizeof(QuadVertex));  // TODO: Change

    vertexArrayBuffer->setupAttributePointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)0);
    vertexArrayBuffer->setupAttributePointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, color));
    vertexArrayBuffer->unbind();
}

void BatchRenderer::pushQuad(Quad quad) {
    quads.push_back(quad);
}

void BatchRenderer::draw() {
    std::vector<QuadVertex> vertices(quads.size() * maxVertex);

    std::array<glm::vec2, vertexPerQuad> defaultPositions = {
        glm::vec2{-0.5f, -0.5f},
        glm::vec2{0.5f, -0.5f},
        glm::vec2{0.5f, 0.5f},
        glm::vec2{-0.5f, 0.5f},
    };

    for (int i = 0; i < quads.size(); i++) {
        Quad quad = quads[i];

        glm::mat4 transform(1.0f);

        transform = glm::scale(transform, {quad.transform.scale, 1.0f});
        transform = glm::rotate(transform, glm::radians(quad.transform.rotationDegrees), {0.0f, 0.0f, 1.0f});
        transform = glm::translate(transform, {quad.transform.position, 0.0f});

        for (int i = 0; i < 4; i++) {
            glm::vec4 currentPosition = glm::vec4(defaultPositions[i].x, defaultPositions[i].y, 0, 1) * transform;

            vertices[i] = QuadVertex{
                {currentPosition.x, currentPosition.y},
                quad.color,
            };
        }
    }

    if (quads.size() > 0) {
        vertexArrayBuffer->bind();

        vertexBuffer->bind();
        vertexBuffer->bufferSubData(&vertices[0], 0, vertexPerQuad * sizeof(QuadVertex));
        
        Renderer::draw(indexPerQuad * quads.size());

        vertexArrayBuffer->unbind();
    }

    quads.clear();
}
