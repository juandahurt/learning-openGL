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
#include "world/camera.h"
#include "world/cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera camera({ 0.0f, 0.0f, 3.f });

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
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
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Perspective", glfwGetPrimaryMonitor(), nullptr);
    if (!window) {
        fprintf(stderr, "Window couldn't be created.");
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW couldn't be initialized!\n");
        return -1;
    }

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_CULL_FACE));

    // just if I want to draw something that has transparency
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Shader shader("src/shaders/shader.glsl");
    shader.bind();

    Renderer renderer;

    float angle = 0;

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    double lastTime = glfwGetTime();
    double lastFrameTime = lastTime;
    double now;
    int frames = 0;

    glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    Cube* cubes[] = {
            new Cube({1, 0, -5}),
            new Cube({3, 0, -5}),
            new Cube({3, 2, -5}),
    };

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();
        now = glfwGetTime();
        Time::deltaTime = now - lastTime;
        lastTime = now;

        if (now - lastFrameTime >= 1.0) {
            lastFrameTime += 1;
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
        }
        frames++;

        // model
        auto translation = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, 0.f));
        auto rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 0.0f));
        auto model = translation;

        // view/camera
        auto view = camera.matrix();

        // projection
        auto projection = glm::perspective(glm::radians(45.f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 1.f, 100.f);

        auto mvp = projection * view * model;
        shader.uniformMat4f("u_mvp", mvp);

//        auto cube = cubes[0];
        for (auto & cube : cubes) {
            renderer.render(cube->vertexBuffer(), cube->indexBuffer(), cube->vertexArray());
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        angle += 0.2;
    }

    glfwTerminate();

    return 0;
}