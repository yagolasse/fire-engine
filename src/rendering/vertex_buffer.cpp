#include "vertex_buffer.hpp"

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

void VertexBuffer::bufferData(const void* data, GLsizeiptr size) const {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer::bufferSubData(const void* data, GLintptr offset, GLsizeiptr size) const {
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
