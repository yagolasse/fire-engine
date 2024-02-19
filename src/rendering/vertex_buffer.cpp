#include "vertex_buffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &handle);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &handle);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, handle);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bufferData(const float* data, GLsizeiptr size) const {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
