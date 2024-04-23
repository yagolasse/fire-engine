#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "element_array_buffer.h"
#include "quad_vertex.h"
#include "shader_program.h"
#include "texture.h"
#include "vertex.h"
#include "vertex_array_buffer.h"
#include "vertex_buffer.h"


class BatchRenderer {
   private:
    std::vector<Quad> quads;

    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<VertexArrayBuffer> vertexArrayBuffer;
    std::unique_ptr<ElementArrayBuffer> elementArrayBuffer;

   public:
    BatchRenderer();
    void pushQuad(Quad quad);
};
