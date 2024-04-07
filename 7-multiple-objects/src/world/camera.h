//
// Created by Juan Hurtado on 4/04/24.
//

#ifndef INC_7_MULTIPLE_OBJECTS_CAMERA_H
#define INC_7_MULTIPLE_OBJECTS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../core.h"

class Camera {
private:
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec2 m_lastCursorPos = { (float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT / 2.f };
    float m_pitch = 0;
    float m_yaw = -90;
public:
    float speed = 0.2f;

    Camera(glm::vec3 position) {
        m_pos = position;
        m_front = { 0, 0, -1 };
        m_up = { 0, 1, 0 };
    }
    glm::mat4 matrix() {
        return glm::lookAt(m_pos, m_pos + m_front, m_up);
    }
    void moveForward() {
        m_pos += m_front * speed;
    }

    void moveBackward() {
        m_pos -= m_front * speed;
    }

    void moveLeft() {
        m_pos -= glm::normalize(glm::cross(m_front, m_up)) * speed;
    }

    void moveRight() {
        m_pos -= glm::normalize(glm::cross(m_up, m_front)) * speed;
    }

    void moveUp() {
        m_pos.y += speed;
    }

    void moveDown() {
        m_pos.y -= speed;
    }

    void accelerate() {
        speed += 0.1;
    }

    void decelerate() {
        speed -= 0.1;
    }

    void mouse(double x, double y) {
        auto xOffset = (float)x - m_lastCursorPos.x;
        auto yOffset = m_lastCursorPos.y - (float)y;
        m_lastCursorPos = { x, y };

        float sensitivity = 0.1;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        m_yaw += xOffset;
        m_pitch += yOffset;

        if(m_pitch > 89.0f)
            m_pitch = 89.0f;
        if(m_pitch < -89.0f)
            m_pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(direction);
    }
};


#endif //INC_7_MULTIPLE_OBJECTS_CAMERA_H
