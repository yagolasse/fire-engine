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
    void bufferData(const void* data, GLsizeiptr size) const;
    void bufferSubData(const void* data, GLintptr offset, GLsizeiptr size) const;

    inline GLuint getHandle() const {
        return handle;
    }
};
