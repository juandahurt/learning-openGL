//
// Created by Juan Hurtado on 16/03/24.
//

#include "Renderer.h"



void Renderer::render(VertexBuffer &vertexBuffer, IndexBuffer &indexBuffer, VertexBufferLayout layout) const {
    vertexBuffer.bind();
    indexBuffer.bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
