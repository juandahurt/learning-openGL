//
// Created by Juan Hurtado on 17/03/24.
//

#ifndef INC_4_ABSTRACTION_INDEXBUFFER_H
#define INC_4_ABSTRACTION_INDEXBUFFER_H

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


#endif //INC_4_ABSTRACTION_INDEXBUFFER_H
