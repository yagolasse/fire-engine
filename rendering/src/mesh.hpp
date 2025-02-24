#ifndef MESH_HPP
#define MESH_HPP

#include <glm.hpp>
#include <vector>

class ShaderProgram;
class VertexBuffer;
class VertexArrayBuffer;
class ElementArrayBuffer;

struct MeshVertex {
    glm::vec3 position;
};

class Mesh {
   private:
    ShaderProgram* shader;
    VertexBuffer* vertexBuffer;
    VertexArrayBuffer* vertexArrayBuffer;
    ElementArrayBuffer* elementArrayBuffer;

    std::vector<MeshVertex> vertices;

   public:
    Mesh();
    ~Mesh();

    void init();
    void draw();
};

#endif
