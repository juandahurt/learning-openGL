//
// Created by Juan Hurtado on 17/03/24.
//

#include "VertexArray.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_id));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::addBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout) {
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
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(0);
}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(m_id));
}