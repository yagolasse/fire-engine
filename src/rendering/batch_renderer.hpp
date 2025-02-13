#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include <memory>
#include <array>
#include <vector>

#include "element_array_buffer.hpp"
#include "quad.hpp"
#include "shader_program.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "vertex_array_buffer.hpp"
#include "vertex_buffer.hpp"

class BatchRenderer {
   private:
    static const int indexPerQuad = 6;
    static const int vertexPerQuad = 4;
    static const int maxQuadsPerDraw = 1024;
    static const int maxIndex = indexPerQuad * maxQuadsPerDraw;
    static const int maxVertex = vertexPerQuad * maxQuadsPerDraw;
    
    std::vector<Quad> quads;
    std::array<QuadVertex, maxVertex> vertices;

    std::unique_ptr<ShaderProgram> shader;
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<VertexArrayBuffer> vertexArrayBuffer;
    std::unique_ptr<ElementArrayBuffer> elementArrayBuffer;

   public:
    BatchRenderer();
    void pushQuad(Quad quad);
    void draw(const float *viewMatrix, const float *projectionMatrix);
};

#endif
