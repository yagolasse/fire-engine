#pragma once

#include <glad/glad.h>

class VertexArrayBuffer {
   private:
    GLuint handle;

   public:
    VertexArrayBuffer();
    ~VertexArrayBuffer();

    void bind() const;
    void unbind() const;
    void setupAttributePointer(int index, GLsizei size) const;

    inline GLuint getHandle() const {
        return handle;
    }
};
