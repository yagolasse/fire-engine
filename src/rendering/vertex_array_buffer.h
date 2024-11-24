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
    void setupFloatAttributePointer(int index, int size, int type, int normalized, int stride, const void* pointer) const;
    void setupIntegerAttributePointer(int index, int size, int type, int stride, const void* pointer) const;

    inline GLuint getHandle() const {
        return handle;
    }
};
