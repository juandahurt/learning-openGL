#include <GL/glew.h>
#include <string>
#include <GLFW/glfw3.h>
#include <cassert>
#include "VertexBuffer.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"

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
    window = glfwCreateWindow(800, 500, "Abstraction", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Window couldn't be created.");
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW couldn't be initialized!\n");
        return -1;
    }

    float vertices[] = {
            -0.5, 0.5,
            -0.5, -0.5,
            0.5, 0.5,
            0.5, -0.5
    };

    unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2
    };

    // allocate VBO and get the ID
    auto vertexBuffer = VertexBuffer(&vertices, sizeof(vertices));

    auto layout = VertexBufferLayout();
    layout.addElement<float>(2);

    /// allocate VAO
    auto vertexArray = VertexArray();
    vertexArray.addBuffer(vertexBuffer, layout);
    auto indexBuffer = IndexBuffer(indices, 6);

    Shader shader("shader.glsl");
    shader.bind();

    float b = 1;
    float increment = 0.1;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.uniform4<float>("u_color", 1.0, b, 0.5, 1);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (b >= 1)
            increment = -0.01;
        if (b < 0)
            increment = 0.01;
        b += increment;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}