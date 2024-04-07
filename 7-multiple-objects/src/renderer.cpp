//
// Created by Juan Hurtado on 25/03/24.
//

#include "renderer.h"

void Renderer::render(VertexBuffer &vertexBuffer, IndexBuffer &indexBuffer, VertexArray &vao) const {
    vertexBuffer.bind();
    indexBuffer.bind();
    vao.bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
    glClearColor(165.f / 255.f, 196.f / 255.f, 212.f / 255.f, 1);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}