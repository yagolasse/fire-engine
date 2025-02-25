#ifndef MESH_HPP
#define MESH_HPP

#include <glm.hpp>
#include <vector>

class Camera;
class ShaderProgram;
class VertexBuffer;
class VertexArrayBuffer;
class ElementArrayBuffer;

struct Transform3D;

struct MeshVertex {
    glm::vec3 position;
};

class Mesh {
   private:
    Transform3D* transform;
    ShaderProgram* shader;
    VertexBuffer* vertexBuffer;
    VertexArrayBuffer* vertexArrayBuffer;
    ElementArrayBuffer* elementArrayBuffer;

    std::vector<MeshVertex> vertices;

   public:
    Mesh();
    ~Mesh();

    void init();
    void draw(Camera* camera);
};

#endif
