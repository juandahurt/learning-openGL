//
// Created by Juan Hurtado on 17/03/24.
//

#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() {
    m_stride = 0;
}

VertexBufferLayout::~VertexBufferLayout(){
}

const std::vector<LayoutElement> &VertexBufferLayout::getElements() const {
    return m_elements;
}

unsigned int VertexBufferLayout::stride() const { return m_stride; }