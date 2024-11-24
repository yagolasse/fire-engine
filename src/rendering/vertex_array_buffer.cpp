#include "vertex_array_buffer.h"

#include <glad/glad.h>

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

void VertexArrayBuffer::setupFloatAttributePointer(int index, int size, int type, int normalized, int stride, const void* pointer) const {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArrayBuffer::setupIntegerAttributePointer(int index, int size, int type, int stride, const void* pointer) const {
    glEnableVertexAttribArray(index);
    glVertexAttribIPointer(index, size, type, stride, pointer);
}
