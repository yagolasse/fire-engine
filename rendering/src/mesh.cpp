#include "mesh.hpp"

#include <gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "assertion.hpp"
#include "camera.hpp"
#include "element_array_buffer.hpp"
#include "renderer.hpp"
#include "resource_loader.hpp"
#include "shader_program.hpp"
#include "transform_3d.hpp"
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

    vertices = std::vector<MeshVertex>(8);

    transform = new Transform3D {
        glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(glm::vec3(0.0f, 45.0f, 0.0f)), glm::vec3(1.0f),
    };
}

Mesh::~Mesh() {
    delete shader;
    delete elementArrayBuffer;
    delete vertexArrayBuffer;
    delete vertexBuffer;
}

void Mesh::init() {
    std::vector<unsigned int> indices(6);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    vertexArrayBuffer->bind();

    elementArrayBuffer->bind();
    elementArrayBuffer->bufferData(&indices[0], indices.size() * sizeof(unsigned int));

    vertexBuffer->bind();
    vertexBuffer->bufferData(nullptr, vertices.size() * sizeof(MeshVertex));

    vertexArrayBuffer->setupFloatAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)0);

    vertexBuffer->unbind();

    elementArrayBuffer->unbind();

    vertexArrayBuffer->unbind();
}

void Mesh::draw(Camera *camera) {

    /**
     *    2 /========/| 3
     *     /        / |
     *    /   1    /  |
     * 3 |========| 2 | 0
     *   |        |  /
     *   |        | /
     * 0 |========|/1
     */


    vertices[0] = MeshVertex{{-0.5f, -0.5f, 0.5f}};
    vertices[1] = MeshVertex{{0.5f, -0.5f, 0.5f}};
    vertices[2] = MeshVertex{{0.5f, 0.5f, 0.5f}};
    vertices[3] = MeshVertex{{-0.5f, 0.5f, 0.5f}};
    vertices[4] = MeshVertex{{0.5f, -0.5f, -0.5f}};
    vertices[5] = MeshVertex{{-0.5f, -0.5f, -0.5f}};
    vertices[6] = MeshVertex{{-0.5f, 0.5f, -0.5f}};
    vertices[7] = MeshVertex{{0.5f, 0.5f, -0.5f}};

    shader->bind();

    shader->setMat4("view", glm::value_ptr(camera->getView()));
    shader->setMat4("projection", glm::value_ptr(camera->getProjection()));

    shader->setMat4("rotation", glm::value_ptr(glm::mat4(transform->rotation)));
    shader->setMat4("scaling", glm::value_ptr(glm::scale(glm::mat4(1.0f), transform->scale)));
    shader->setMat4("translation", glm::value_ptr(glm::translate(glm::mat4(1.0f), transform->position)));
    
    vertexArrayBuffer->bind();

    elementArrayBuffer->bind();

    vertexBuffer->bind();
    vertexBuffer->bufferSubData(&vertices[0], 0, 4 * sizeof(MeshVertex));

    Renderer::getInstance()->draw(6);

    vertexBuffer->unbind();

    elementArrayBuffer->unbind();

    vertexArrayBuffer->unbind();

    shader->unbind();
}
