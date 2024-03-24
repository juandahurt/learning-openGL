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
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    window = glfwCreateWindow(800, 500, "Texture", nullptr, nullptr);
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

    // just if I want to draw something that has transparency
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    float vertices[] = {
            100, 100, 0, 0, // bottom left
            200, 100, 1, 0, // bottom right
            200, 200, 1, 1, // top right
            100, 200, 0, 1, // top left
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3 ,0
    };

    // allocate VBO and get the ID
    auto vertexBuffer = VertexBuffer(&vertices, sizeof(vertices));

    // VBO: (float, float), (float, float)
    auto layout = VertexBufferLayout();
    layout.addElement<float>(2);
    layout.addElement<float>(2);

    /// allocate VAO
    auto vertexArray = VertexArray();
    vertexArray.addBuffer(vertexBuffer, layout);
    auto indexBuffer = IndexBuffer(indices, 6);

    glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 500.0, -1.0, 1.0);

    Shader shader("shader.glsl");
    shader.bind();

    Texture texture("res/minecraft.png");
    texture.bind();
    shader.uniform1i("u_texture", 0); // we pass the slot we are using
    shader.uniformMat4f("u_projection", projection);

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();
        renderer.render(vertexBuffer, indexBuffer, layout);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}