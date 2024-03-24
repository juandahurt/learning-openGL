//
// Created by Juan Hurtado on 17/03/24.
//

#ifndef INC_4_ABSTRACTION_VERTEXARRAY_H
#define INC_4_ABSTRACTION_VERTEXARRAY_H

#include "core.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_id;
public:
    VertexArray();
    ~VertexArray();
    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
    void bind() const;
};


#endif //INC_4_ABSTRACTION_VERTEXARRAY_H
