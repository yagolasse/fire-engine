#pragma once

#include <glad/glad.h>

class VertexBuffer {
   private:
    GLuint handle;

   public:
    VertexBuffer();
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
    void bufferData(const float* data, GLsizeiptr size) const;

    inline GLuint getHandle() const {
        return handle;
    }
};
