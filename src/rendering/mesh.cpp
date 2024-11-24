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

    vertexArrayBuffer->setupFloatAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    vertexArrayBuffer->setupFloatAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    vertexArrayBuffer->setupFloatAttributePointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));
    vertexArrayBuffer->setupFloatAttributePointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

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

void Mesh::scale(glm::vec3 scale) {
    transform = glm::scale(transform, scale);
}

void Mesh::rotate(float angle, glm::vec3 axis) {
    transform = glm::rotate(transform, glm::radians(angle), axis);
}

void Mesh::translate(glm::vec3 movement) {
    transform = glm::translate(transform, movement);
}

std::unique_ptr<Mesh> Mesh::createQuadMesh(glm::vec3 color, std::shared_ptr<Texture> texture) {
    std::vector<Vertex> vertices = {
        Vertex { { -0.5f, -0.5f, 0.0f, }, color, { 0.0f, 0.0f, } },
        Vertex { { 0.5f,  -0.5f, 0.0f, }, color, { 1.0f, 0.0f, } },
        Vertex { { 0.5f,   0.5f, 0.0f, }, color, { 1.0f, 1.0f, } },
        Vertex { { -0.5f,  0.5f, 0.0f, }, color, { 0.0f, 1.0f, } },
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    return std::move(std::make_unique<Mesh>(vertices, indices, std::vector { texture }));
}

std::unique_ptr<Mesh> Mesh::createCubeMesh(glm::vec3 color, std::shared_ptr<Texture> texture) {
    std::vector<Vertex> vertices = {
        Vertex { { -0.5f, -0.5f, -0.5f, }, color, { 0.0f, 0.0f, }, { 0.0f, 0.0f, -1.0f } },
        Vertex { { 0.5f, -0.5f, -0.5f, }, color, { 1.0f, 0.0f, },  { 0.0f, 0.0f, -1.0f } },
        Vertex { { 0.5f,  0.5f, -0.5f, }, color, { 1.0f, 1.0f, }, { 0.0f, 0.0f, -1.0f } },
        Vertex { { -0.5f,  0.5f, -0.5f, }, color, { 0.0f, 1.0f, }, { 0.0f, 0.0f, -1.0f }  },

        Vertex { { -0.5f, -0.5f,  0.5f, }, color, { 0.0f, 0.0f, },  { 0.0f, 0.0f, 1.0f } },
        Vertex { { 0.5f, -0.5f,  0.5f, }, color, { 1.0f, 0.0f, }, { 0.0f, 0.0f, 1.0f }  },
        Vertex { { 0.5f,  0.5f,  0.5f, }, color, { 1.0f, 1.0f, },  { 0.0f, 0.0f, 1.0f } },
        Vertex { { -0.5f,  0.5f,  0.5f, }, color, { 0.0f, 1.0f, },  { 0.0f, 0.0f, 1.0f } },

        Vertex { { -0.5f,  0.5f,  0.5f, }, color, { 1.0f, 0.0f, }, { -1.0f, 0.0f, 0.0f } },
        Vertex { { -0.5f,  0.5f, -0.5f, }, color, { 1.0f, 1.0f, }, { -1.0f, 0.0f, 0.0f } },
        Vertex { { -0.5f, -0.5f, -0.5f, }, color, { 0.0f, 1.0f, }, { -1.0f, 0.0f, 0.0f }  },
        Vertex { { -0.5f, -0.5f,  0.5f, }, color, { 0.0f, 0.0f, }, { -1.0f, 0.0f, 0.0f }  },

        Vertex { { 0.5f,  0.5f,  0.5f, }, color, { 1.0f, 0.0f, }, { 1.0f, 0.0f, 0.0f } },
        Vertex { { 0.5f,  0.5f, -0.5f, }, color, { 1.0f, 1.0f, }, { 1.0f, 0.0f, 0.0f } },
        Vertex { { 0.5f, -0.5f, -0.5f, }, color, { 0.0f, 1.0f, }, { 1.0f, 0.0f, 0.0f } },
        Vertex { { 0.5f, -0.5f,  0.5f, }, color, { 0.0f, 0.0f, }, { 1.0f, 0.0f, 0.0f }  },

        Vertex { { -0.5f, -0.5f, -0.5f, }, color, { 0.0f, 1.0f, }, { 0.0f, -1.0f, 0.0f } },
        Vertex { { 0.5f, -0.5f, -0.5f, }, color, { 1.0f, 1.0f, }, { 0.0f, -1.0f, 0.0f }  },
        Vertex { { 0.5f, -0.5f,  0.5f, }, color, { 1.0f, 0.0f, }, { 0.0f, -1.0f, 0.0f }  },
        Vertex { { -0.5f, -0.5f,  0.5f, }, color, { 0.0f, 0.0f, }, { 0.0f, -1.0f, 0.0f } },

        Vertex { { -0.5f,  0.5f, -0.5f, }, color, { 0.0f, 1.0f, }, { 0.0f, 1.0f, 0.0f } },
        Vertex { { 0.5f,  0.5f, -0.5f, }, color, { 1.0f, 1.0f, }, { 0.0f, 1.0f, 0.0f } },
        Vertex { { 0.5f,  0.5f,  0.5f, }, color, { 1.0f, 0.0f, }, { 0.0f, 1.0f, 0.0f } },
        Vertex { { -0.5f,  0.5f,  0.5f, }, color, { 0.0f, 0.0f, }, { 0.0f, 1.0f, 0.0f } },
    };

    std::vector<unsigned int> indices(36);

    int index = 0;

    for (int i = 0; i < 36; i += 6) {
        indices[0 + i] = 0 + index;
        indices[1 + i] = 1 + index;
        indices[2 + i] = 2 + index;
        indices[3 + i] = 2 + index;
        indices[4 + i] = 3 + index;
        indices[5 + i] = 0 + index;
        index += 4;
    }

    return std::move(std::make_unique<Mesh>(vertices, indices, std::vector { texture }));
}
