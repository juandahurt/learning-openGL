//
// Created by Juan Hurtado on 16/03/24.
//

#ifndef INC_4_ABSTRACTION_VERTEXBUFFER_H
#define INC_4_ABSTRACTION_VERTEXBUFFER_H

class VertexBuffer {
private:
    /// Identifies this buffer
    unsigned int m_id;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};


#endif //INC_4_ABSTRACTION_VERTEXBUFFER_H
