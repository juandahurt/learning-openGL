//
// Created by Juan Hurtado on 25/03/24.
//

#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout() {
    m_stride = 0;
}

VertexBufferLayout::~VertexBufferLayout(){
}

const std::vector<LayoutElement> &VertexBufferLayout::getElements() const {
    return m_elements;
}

unsigned int VertexBufferLayout::stride() const { return m_stride; }