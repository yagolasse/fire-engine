#pragma once

#include <memory>
#include <vector>

#include "vertex.h"
#include "vertex_buffer.h"
#include "vertex_array_buffer.h"
#include "element_array_buffer.h"

class Mesh {
   private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::unique_ptr<VertexBuffer> uvVertexBuffer;
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<VertexArrayBuffer> vertexArrayBuffer;
    std::unique_ptr<ElementArrayBuffer> elementArrayBuffer;

   public:
    Mesh(std::vector<Vertex> vertexData, std::vector<unsigned int> indexData);
};
