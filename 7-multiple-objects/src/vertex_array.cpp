//
// Created by Juan Hurtado on 25/03/24.
//

#include "core.h"
#include "vertex_array.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_id));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout) const {
    bind();
    vertexBuffer.bind();
    auto elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        auto &element = elements[i];
        GLCall(glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.stride(), (void*)offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * sizeof(float); // TODO: add func that return size of type
    }
}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(m_id));
}