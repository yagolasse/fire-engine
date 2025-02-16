#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include <memory>
#include <array>
#include <vector>

#include "quad.hpp"

class ShaderProgram;
class VertexBuffer;
class VertexArrayBuffer;
class ElementArrayBuffer;

class BatchRenderer {
   private:
    static BatchRenderer* instance;

    static const int indexPerQuad = 6;
    static const int vertexPerQuad = 4;
    static const int maxQuadsPerDraw = 1024;
    static const int maxIndex = indexPerQuad * maxQuadsPerDraw;
    static const int maxVertex = vertexPerQuad * maxQuadsPerDraw;
    
    std::vector<Quad> quads;
    std::array<QuadVertex, maxVertex> vertices;

    ShaderProgram* shader;
    VertexBuffer* vertexBuffer;
    VertexArrayBuffer* vertexArrayBuffer;
    ElementArrayBuffer* elementArrayBuffer;

    BatchRenderer();
    ~BatchRenderer();

   public:
    static BatchRenderer* getInstance();
    static void disposeInstance();

    void init();
    void pushQuad(Quad quad);
    void draw(const float *viewMatrix, const float *projectionMatrix);
};

#endif
