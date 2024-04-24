#include "batch_renderer.h"

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "quad.h"
#include "renderer.h"

BatchRenderer::BatchRenderer() {
    vertexBuffer = std::make_unique<VertexBuffer>();
    vertexArrayBuffer = std::make_unique<VertexArrayBuffer>();
    elementArrayBuffer = std::make_unique<ElementArrayBuffer>();

    std::array<unsigned int, 6> indices;

    int index = 0;

    for (int i = 0; i < 6; i += 6) {
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
    vertexBuffer->bufferData(nullptr, 4 * sizeof(QuadVertex)); // TODO: Change

    vertexArrayBuffer->setupAttributePointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)0);
    vertexArrayBuffer->setupAttributePointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, color));

    vertexArrayBuffer->unbind();
}

void BatchRenderer::pushQuad(Quad quad) {
    quads.push_back(quad);
}

void BatchRenderer::draw() {
    std::array<QuadVertex, 4> vertices;

    std::array<glm::vec2, 4> defaultPositions = {
        glm::vec2{-0.5f, -0.5f},
        glm::vec2{0.5f, -0.5f},
        glm::vec2{0.5f, 0.5f},
        glm::vec2{-0.5f, 0.5f},
    };
    
    for (int i = 0; i < quads.size(); i++) {
        Quad quad = quads[i];

        bool isRotated = quad.transform.rotationDegrees != 0;

        glm::mat4 transform(1.0f);

        if (isRotated) {
            transform = glm::translate(transform, {quad.transform.position, 0.0f});
            transform = glm::rotate(transform, glm::radians(quad.transform.rotationDegrees), {0.0f, 0.0f, 1.0f});
            transform = glm::scale(transform, {quad.transform.scale, 1.0f});
        }

        for (int i = 0; i < 4; i++) {
            glm::vec4 currentPosition(quad.transform.position.x + (defaultPositions[i].x * quad.transform.scale.x),
                                    quad.transform.position.y + (defaultPositions[i].y * quad.transform.scale.y), 0, 1);
            if (isRotated) {
                currentPosition = glm::vec4(defaultPositions[i].x, defaultPositions[i].y, 0, 1) * transform;
            }

            vertices[i] = QuadVertex{
                {currentPosition.x, currentPosition.y},
                quad.color,
            };
        }
    }

    if (quads.size() > 0) { 
        vertexArrayBuffer->bind();

        vertexBuffer->bind();
        vertexBuffer->bufferSubData(&vertices[0], 0, 4 * sizeof(QuadVertex));

        Renderer::draw(6);

        vertexArrayBuffer->unbind();
    }
}
