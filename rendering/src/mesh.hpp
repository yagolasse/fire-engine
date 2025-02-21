#ifndef MESH_HPP
#define MESH_HPP

#include <glm.hpp>

class ShaderProgram;
class VertexBuffer;
class VertexArrayBuffer;
class ElementArrayBuffer;

struct MeshVertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::i8vec4 color;
    glm::uint8_t textureIndex;
};

class Mesh {
   private:
    ShaderProgram* shader;
    VertexBuffer* vertexBuffer;
    VertexArrayBuffer* vertexArrayBuffer;
    ElementArrayBuffer* elementArrayBuffer;

   public:
    Mesh();
    ~Mesh();

    void init();
};

#endif
