//
// Created by Juan Hurtado on 25/03/24.
//

#include "vertex.h"

Vertex::Vertex(float x, float y, float z) {
    m_pos = { x, y, z };
    float r = (float)random() / (float)RAND_MAX;
    float g = (float)random() / (float)RAND_MAX;
    float b = (float)random() / (float)RAND_MAX;
    m_color = { r, g, b };
}

Vertex::Vertex() {
    m_pos = {0 ,0, 0};
    m_color = { 0, 0, 0 };
}
