//
// Created by Juan Hurtado on 16/03/24.
//

#ifndef INC_4_ABSTRACTION_RENDERER_H
#define INC_4_ABSTRACTION_RENDERER_H

#include "core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <iostream>

class Renderer {
public:
    Renderer(){}
    void clear() const;
    void render(VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer, VertexBufferLayout layout) const;
};


#endif //INC_4_ABSTRACTION_RENDERER_H
