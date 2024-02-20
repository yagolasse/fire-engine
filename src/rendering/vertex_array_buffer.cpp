#include "vertex_array_buffer.h"

VertexArrayBuffer::VertexArrayBuffer() {
    glGenVertexArrays(1, &handle);
}

VertexArrayBuffer::~VertexArrayBuffer() {
    glDeleteVertexArrays(1, &handle);
}

void VertexArrayBuffer::bind() const {
    glBindVertexArray(handle);
}

void VertexArrayBuffer::unbind() const {
    glBindVertexArray(0);
}

void VertexArrayBuffer::setupAttributePointer(int index, GLsizei size) const {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void *)0);
    glEnableVertexAttribArray(index);
}
