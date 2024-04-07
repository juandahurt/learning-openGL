//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_VERTEX_BUFFER_LAYOUT_H
#define INC_6_PERSPECTIVE_VERTEX_BUFFER_LAYOUT_H

#include "core.h"
#include <vector>

struct LayoutElement {
    unsigned int type;
    unsigned int count;
};

/// This class represents the layout a vertex
class VertexBufferLayout {
private:
    unsigned int m_stride;
    std::vector<LayoutElement> m_elements;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    void addElement(unsigned int count) {}

    template<>
    void addElement<float>(unsigned int count) {
        m_stride += sizeof(GLfloat) * count;
        m_elements.push_back({ GL_FLOAT, count});
    }

    const std::vector<LayoutElement>& getElements() const;
    unsigned int stride() const;
};



#endif //INC_6_PERSPECTIVE_VERTEX_BUFFER_LAYOUT_H
