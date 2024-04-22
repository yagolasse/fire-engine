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
    void setupAttributePointer(int index, int size, int type, int normalized, int stride, const void* pointer) const;

    inline GLuint getHandle() const {
        return handle;
    }
};
