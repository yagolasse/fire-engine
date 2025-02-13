#ifndef ELEMENT_ARRAY_BUFFER_HPP
#define ELEMENT_ARRAY_BUFFER_HPP

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

#endif
