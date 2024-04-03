//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_INDEX_BUFFER_H
#define INC_6_PERSPECTIVE_INDEX_BUFFER_H

#include "core.h"

class IndexBuffer {
private:
    unsigned int m_id;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();
    unsigned int count() const;
    void bind();
    void unbind();
};


#endif //INC_6_PERSPECTIVE_INDEX_BUFFER_H
