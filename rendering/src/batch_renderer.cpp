#include "batch_renderer.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "assertion.hpp"
#include "element_array_buffer.hpp"
#include "error.hpp"
#include "quad.hpp"
#include "renderer.hpp"
#include "resource_loader.hpp"
#include "shader.hpp"
#include "shader_program.hpp"
#include "texture.hpp"
#include "texture_storage.hpp"
#include "vertex.hpp"
#include "vertex_array_buffer.hpp"
#include "vertex_buffer.hpp"

BatchRenderer *BatchRenderer::instance = nullptr;

BatchRenderer *BatchRenderer::getInstance() {
    if (instance == nullptr) {
        instance = new BatchRenderer();
    }
    return instance;
}

void BatchRenderer::disposeInstance() {
    delete instance;
}

BatchRenderer::BatchRenderer() {
}

BatchRenderer::~BatchRenderer() {
    delete shader;
    delete elementArrayBuffer;
    delete vertexArrayBuffer;
    delete vertexBuffer;
}

void BatchRenderer::init() {
    vertexBuffer = new VertexBuffer();
    vertexArrayBuffer = new VertexArrayBuffer();
    elementArrayBuffer = new ElementArrayBuffer();

    std::string vertexString = ResourceLoader::readStringFromFile("resources/quad_vertex_shader.glsl");
    std::string fragmentString = ResourceLoader::readStringFromFile("resources/quad_fragment_shader.glsl");

    shader = new ShaderProgram();

    shader->linkShader(vertexString.c_str(), fragmentString.c_str());

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
    vertexArrayBuffer->setupFloatAttributePointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(QuadVertex), (void *)offsetof(QuadVertex, color));
    vertexArrayBuffer->setupFloatAttributePointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void *)offsetof(QuadVertex, uv));
    vertexArrayBuffer->setupIntegerAttributePointer(3, 1, GL_UNSIGNED_BYTE, sizeof(QuadVertex), (void *)offsetof(QuadVertex, textureIndex));

    vertexBuffer->unbind();

    elementArrayBuffer->unbind();

    vertexArrayBuffer->unbind();

    TextureStorage::getInstance()->bind();
}

void BatchRenderer::pushQuad(Quad quad) {
    quads.push_back(quad);
}

void BatchRenderer::draw(const float *viewMatrix, const float *projectionMatrix) {
    Renderer::getInstance()->clear();

    TextureStorage::getInstance()->bind();

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
            auto midPoint = std::chrono::high_resolution_clock::now();

            vertexArrayBuffer->bind();

            elementArrayBuffer->bind();

            vertexBuffer->bind();
            vertexBuffer->bufferSubData(&vertices[0], 0, vertexIndex * sizeof(QuadVertex));

            Renderer::getInstance()->draw(indexPerQuad * vertexIndex / vertexPerQuad);

            vertexBuffer->unbind();

            elementArrayBuffer->unbind();

            vertexArrayBuffer->unbind();

            vertexIndex = 0;
        }
    }

    shader->unbind();

    quads.clear();
}
