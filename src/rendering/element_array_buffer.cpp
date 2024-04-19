#include "element_array_buffer.h"

ElementArrayBuffer::ElementArrayBuffer() {
    glGenBuffers(1, &handle);
}

ElementArrayBuffer::~ElementArrayBuffer() {
    glDeleteBuffers(1, &handle);
}

void ElementArrayBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
}

void ElementArrayBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementArrayBuffer::bufferData(const unsigned int* data, GLsizeiptr size) const {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
