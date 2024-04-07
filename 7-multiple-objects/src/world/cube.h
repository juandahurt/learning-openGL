//
// Created by Juan Hurtado on 4/04/24.
//

#ifndef INC_7_MULTIPLE_OBJECTS_CUBE_H
#define INC_7_MULTIPLE_OBJECTS_CUBE_H

#include <glm/glm.hpp>
#include "../vertex_buffer.h"
#include "../vertex_buffer_layout.h"
#include "../index_buffer.h"
#include "../vertex_array.h"

class Cube {
private:
    glm::vec3           m_pos;
    VertexBuffer*       m_vertexBuffer;
    VertexBufferLayout* m_bufferLayout;
    IndexBuffer*        m_indexBuffer;
    VertexArray*        m_vertexArray;
public:
    Cube(glm::vec3 pos);
    ~Cube();

    VertexBuffer& vertexBuffer();
    IndexBuffer& indexBuffer();
    VertexBufferLayout& vertexBufferLayout();
    VertexArray& vertexArray();
};


#endif //INC_7_MULTIPLE_OBJECTS_CUBE_H
