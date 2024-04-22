#pragma once

#include <memory>
#include <vector>

#include "element_array_buffer.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"

class Mesh {
   private:
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;

    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<VertexArrayBuffer> vertexArrayBuffer;
    std::unique_ptr<ElementArrayBuffer> elementArrayBuffer;

   public:
    Mesh(std::vector<Vertex> vertexData, std::vector<Texture> textureData, std::vector<unsigned int> indexData);
    ~Mesh();
    void draw(std::shared_ptr<ShaderProgram> shader);
};
