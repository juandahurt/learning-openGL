//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_VERTEX_ARRAY_H
#define INC_6_PERSPECTIVE_VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
private:
    unsigned int m_id;
public:
    VertexArray();
    ~VertexArray();
    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
    void bind() const;
};


#endif //INC_6_PERSPECTIVE_VERTEX_ARRAY_H
