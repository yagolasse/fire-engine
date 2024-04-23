#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "element_array_buffer.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"

class Mesh {
   private:
    glm::mat4 transform;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<VertexArrayBuffer> vertexArrayBuffer;
    std::unique_ptr<ElementArrayBuffer> elementArrayBuffer;

   public:
    Mesh(
        std::vector<Vertex> vertexData,
        std::vector<unsigned int> indexData,
        std::vector<std::shared_ptr<Texture>> textureData
    );
    ~Mesh();
    void draw(std::shared_ptr<ShaderProgram> shader, std::shared_ptr<Camera> camera);

    static std::unique_ptr<Mesh> createQuadMesh(std::shared_ptr<Texture> texture);
};
