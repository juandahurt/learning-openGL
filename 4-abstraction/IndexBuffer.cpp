//
// Created by Juan Hurtado on 17/03/24.
//

#include "IndexBuffer.h"
#include <cassert>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) {
    m_count = count;
    GLCall(glGenBuffers(1, &m_id));
    bind();
    // if I put `sizeof(data)` doesn't work :/ (?)
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_id));
}

void IndexBuffer::bind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}