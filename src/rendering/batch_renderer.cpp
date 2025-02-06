#include "batch_renderer.h"

#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>

#include "assertion.h"
#include "element_array_buffer.h"
#include "error.h"
#include "quad.h"
#include "renderer.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"

BatchRenderer::BatchRenderer() {
    vertexBuffer = std::make_unique<VertexBuffer>();
    vertexArrayBuffer = std::make_unique<VertexArrayBuffer>();
    elementArrayBuffer = std::make_unique<ElementArrayBuffer>();

    std::ifstream fragFileStream("../resources/quad_fragment_shader.glsl");
    std::ifstream vertFileStream("../resources/quad_vertex_shader.glsl");

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

    shader = std::make_unique<ShaderProgram>(std::move(vertexShader), std::move(fragmentShader));

    for (int i = 0; i < maxVertex; i++) {
        vertices[i] = QuadVertex{
            glm::vec2(),
            glm::vec4(1.0f),
            glm::vec2(),
        };
    }
    std::vector<unsigned int> indices(maxIndex);

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

    vertexArrayBuffer->setupFloatAttributePointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void *)0);
    vertexArrayBuffer->setupFloatAttributePointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(QuadVertex),
                                                  (void *)offsetof(QuadVertex, color));
    vertexArrayBuffer->setupFloatAttributePointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex),
                                                  (void *)offsetof(QuadVertex, uv));
    vertexArrayBuffer->setupIntegerAttributePointer(3, 1, GL_UNSIGNED_BYTE, sizeof(QuadVertex),
                                                    (void *)offsetof(QuadVertex, textureIndex));
    vertexArrayBuffer->unbind();
}

void BatchRenderer::pushQuad(Quad quad) {
    quads.push_back(quad);
}

void BatchRenderer::draw(const float *viewMatrix, const float *projectionMatrix) {
    Renderer::clear();

    shader->bind();
    shader->setInt("textures", 0);
    shader->setMat4("view", viewMatrix);
    shader->setMat4("projection", projectionMatrix);

    std::array<glm::vec2, vertexPerQuad> defaultPositions = {
        glm::vec2{-0.5f, -0.5f},
        glm::vec2{0.5f, -0.5f},
        glm::vec2{0.5f, 0.5f},
        glm::vec2{-0.5f, 0.5f},
    };

    std::array<glm::vec2, 4> defaultUvMapping = {
        glm::vec2{0.0f, 0.0f},
        glm::vec2{1.0f, 0.0f},
        glm::vec2{1.0f, 1.0f},
        glm::vec2{0.0f, 1.0f},
    };

    int vertexIndex = 0;

    for (int quadIndex = 0; quadIndex < quads.size(); quadIndex++) {
        Quad quad = quads[quadIndex];

        glm::mat4 transform = glm::mat4(1.0f);

        transform = glm::translate(transform, {quad.transform.position, 0.0f});
        transform = glm::rotate(transform, glm::radians(quad.transform.rotationDegrees), {0.0f, 0.0f, 1.0f});
        transform = glm::scale(transform, {quad.transform.scale, 1.0f});

        for (int i = 0; i < 4; i++) {
            glm::vec4 currentPosition = transform * glm::vec4(defaultPositions[i].x, defaultPositions[i].y, 0, 1);

            vertices[vertexIndex].position.x = currentPosition.x;
            vertices[vertexIndex].position.y = currentPosition.y;

            vertices[vertexIndex].color.r = quad.color.r * 255;
            vertices[vertexIndex].color.g = quad.color.g * 255;
            vertices[vertexIndex].color.b = quad.color.b * 255;
            vertices[vertexIndex].color.a = quad.color.a * 255;

            vertices[vertexIndex].uv.x = quad.uv[i].x;
            vertices[vertexIndex].uv.y = quad.uv[i].y;

            vertices[vertexIndex].textureIndex = quad.textureIndex;

            vertexIndex++;
        }

        if (vertexIndex == maxVertex || quadIndex == quads.size() - 1) {
            vertexArrayBuffer->bind();

            vertexBuffer->bind();
            vertexBuffer->bufferSubData(&vertices[0], 0, vertexIndex * sizeof(QuadVertex));

            Renderer::draw(indexPerQuad * vertexIndex / vertexPerQuad);

            vertexBuffer->unbind();

            vertexArrayBuffer->unbind();

            vertexIndex = 0;
        }
    }

    shader->unbind();

    quads.clear();
}
