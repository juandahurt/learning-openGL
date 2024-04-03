#include <GL/glew.h>
#include <string>
#include <GLFW/glfw3.h>
#include <cassert>
#include "vertex_buffer.h"
#include "Renderer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include "Shader.h"
#include "vertex.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WINDOW_WIDTH 2560.0
#define WINDOW_HEIGHT 1440.0

double deltaTime = 0;

class Camera {
private:
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec2 m_lastCursorPos = { (float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT / 2.f };
    float m_pitch = 0;
    float m_yaw = -90;
public:
    float speed = fmax(0.1f * (float)deltaTime, 0.1f);

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

Camera camera({ 0.0f, 0.0f, 3.f });

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::cout << camera.speed << std::endl;
    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_W) {
        camera.moveForward();
    }
    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_S) {
        camera.moveBackward();
    }
    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_A) {
        camera.moveLeft();
    }
    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_D) {
        camera.moveRight();
    }
    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_UP) {
        camera.moveUp();
    }
    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_DOWN) {
        camera.moveDown();
    }

    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_O) {
        camera.decelerate();
    }
    if ((action == GLFW_REPEAT || action == GLFW_PRESS) && key == GLFW_KEY_P) {
        camera.accelerate();
    }
}



void mouseCallback(GLFWwindow *window, double x, double y) {
    camera.mouse(x, y);
}

int main() {
    GLFWwindow *window;

    if (!glfwInit()) {
        fprintf(stderr, "GLEW couldn't be initialized!\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Perspective", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Window couldn't be created.");
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW couldn't be initialized!\n");
        return -1;
    }

    GLCall(glEnable(GL_CULL_FACE));
//    GLCall(glFrontFace(GL_CW));
//    GLCall(glCullFace(GL_BACK));

    // just if I want to draw something that has transparency
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

//    float vertices[] = {
//            100, 100, 0, 0, // bottom left
//            200, 100, 1, 0, // bottom right
//            200, 200, 1, 1, // top right
//            100, 200, 0, 1, // top left
//    };

    Vertex vertices[] = {
        { 0.5, 0.5, 0.5 },
        { -0.5, 0.5, -0.5 },
        { -0.5, 0.5, 0.5 },
        { 0.5, -0.5, -0.5 },
        { -0.5, -0.5, -0.5 },
        { 0.5, 0.5, -0.5 },
        { 0.5, -0.5, 0.5 },
        { -0.5, -0.5, 0.5 },
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 3 ,4,
            5, 6, 3,
            7, 3, 6,
            2, 4, 7,
            0, 7, 6,
            0, 5, 1,
            1, 5, 3,
            5, 0, 6,
            7, 4, 3,
            2, 1, 4,
            0, 2, 7
    };

    // allocate VBO and get the ID
    auto vertexBuffer = VertexBuffer(&vertices, sizeof(vertices));

    // VBO: (float, float, float), (float, float, float)
    auto layout = VertexBufferLayout();
    layout.addElement<float>(3);
    layout.addElement<float>(3);

    /// allocate VAO
    auto vertexArray = VertexArray();
    vertexArray.addBuffer(vertexBuffer, layout);
    auto indexBuffer = IndexBuffer(indices, 36);

    Shader shader("src/shaders/shader.glsl");
    shader.bind();

    Renderer renderer;

    float angle = 0;

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    double lastTime = glfwGetTime();
    double now = 0;

    glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;


        // model
        auto translation = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, 0.f));
        auto rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        auto model = translation * rotation;

        // view/camera
        auto view = camera.matrix();

        // projection
        auto projection = glm::perspective(glm::radians(45.f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 1.f, 100.f);

        auto mvp = projection * view * model;
        shader.uniformMat4f("u_mvp", mvp);

        renderer.render(vertexBuffer, indexBuffer, layout);

        glfwSwapBuffers(window);
        glfwPollEvents();

        angle += 0.2;
    }

    glfwTerminate();

    return 0;
}
