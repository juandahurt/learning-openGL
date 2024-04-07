//
// Created by Juan Hurtado on 4/04/24.
//

#include "cube.h"
#include "../vertex.h"

Cube::Cube(glm::vec3 pos) {
    m_pos = pos;
    Vertex vertices[] = {
        { 0.5f + pos.x, 0.5f + pos.y, 0.5f + pos.z },
        { -0.5f + pos.x, 0.5f + pos.y, -0.5f + pos.z },
        { -0.5f + pos.x, 0.5f + pos.y, 0.5f + pos.z },
        { 0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z },
        { -0.5f + pos.x, -0.5f + pos.y, -0.5f + pos.z },
        { 0.5f + pos.x, 0.5f + pos.y, -0.5f + pos.z },
        { 0.5f + pos.x, -0.5f + pos.y, 0.5f + pos.z },
        { -0.5f + pos.x, -0.5f + pos.y, 0.5f + pos.z },
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 3 ,4,
            5, 6, 3,
            7, 3, 6,
            2, 4, 7,
            0, 7, 6,
            0, 5, 1,
            1, 5, 3,
            5, 0, 6,
            7, 4, 3,
            2, 1, 4,
            0, 2, 7
    };
    m_vertexBuffer = new VertexBuffer(&vertices, sizeof(vertices));
    m_bufferLayout = new VertexBufferLayout();
    m_bufferLayout->addElement<float>(3);
    m_bufferLayout->addElement<float>(3);

    m_vertexArray = new VertexArray();
    m_vertexArray->addBuffer(*m_vertexBuffer, *m_bufferLayout);
    m_indexBuffer = new IndexBuffer(indices, 36);
}

Cube::~Cube() {
    delete m_vertexBuffer;
    delete m_indexBuffer;
    delete m_vertexArray;
    delete m_bufferLayout;
}

VertexBuffer &Cube::vertexBuffer() {
    return *m_vertexBuffer;
}

IndexBuffer &Cube::indexBuffer() {
    return *m_indexBuffer;
}

VertexBufferLayout &Cube::vertexBufferLayout() {
    return *m_bufferLayout;
}

VertexArray &Cube::vertexArray() {
    return *m_vertexArray;
}
