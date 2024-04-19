#pragma once

#include <glad/glad.h>

class ElementArrayBuffer {
   private:
    GLuint handle;

   public:
    ElementArrayBuffer();
    ~ElementArrayBuffer();

    void bind() const;
    void unbind() const;
    void bufferData(const unsigned int* data, GLsizeiptr size) const;

    inline GLuint getHandle() const {
        return handle;
    }
};
