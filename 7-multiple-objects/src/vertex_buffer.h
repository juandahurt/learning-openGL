//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_VERTEX_BUFFER_H
#define INC_6_PERSPECTIVE_VERTEX_BUFFER_H


class VertexBuffer {
private:
    /// Identifies this buffer
    unsigned int m_id;
public:
    VertexBuffer(const void* data, unsigned int size);

    VertexBuffer();

    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};


#endif //INC_6_PERSPECTIVE_VERTEX_BUFFER_H
