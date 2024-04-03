//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_RENDERER_H
#define INC_6_PERSPECTIVE_RENDERER_H

#include "core.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"

#include <iostream>

class Renderer {
public:
    Renderer(){}
    void clear() const;
    void render(VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer, VertexBufferLayout layout) const;
};

#endif //INC_6_PERSPECTIVE_RENDERER_H
