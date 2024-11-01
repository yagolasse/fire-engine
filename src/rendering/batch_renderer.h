#pragma once

#include <memory>
#include <array>
#include <vector>

#include "camera.h"
#include "element_array_buffer.h"
#include "quad.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"

class BatchRenderer {
   private:
    static const int indexPerQuad = 6;
    static const int vertexPerQuad = 4;
    static const int maxQuadsPerDraw = 1000;
    static const int maxIndex = indexPerQuad * maxQuadsPerDraw;
    static const int maxVertex = vertexPerQuad * maxQuadsPerDraw;
    
    std::vector<Quad> quads;
    std::array<QuadVertex, maxVertex> vertices;

    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<VertexArrayBuffer> vertexArrayBuffer;
    std::unique_ptr<ElementArrayBuffer> elementArrayBuffer;

   public:
    BatchRenderer();
    void pushQuad(Quad quad);
    void draw();
};
