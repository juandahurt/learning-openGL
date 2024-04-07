//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_VERTEX_H
#define INC_6_PERSPECTIVE_VERTEX_H


#include <glm/glm.hpp>

class Vertex {
private:
    glm::vec3 m_pos;
    glm::vec3 m_color;
public:
    Vertex(float x, float y, float z);
    Vertex();
};


#endif //INC_6_PERSPECTIVE_VERTEX_H
