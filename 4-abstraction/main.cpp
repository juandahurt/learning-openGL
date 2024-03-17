#include <GL/glew.h>
#include <string>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include "VertexBuffer.h"
#include "Renderer.h"
#include "IndexBuffer.h"

struct ShadersSource {
    std::string vertexShader;
    std::string fragmentShader;
};
enum ShaderType {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

ShadersSource readShaders(const std::string &path) {
    std::ifstream stream(path);
    std::string line;

    if (!stream.is_open()) {
        fprintf(stderr, "ERROR: file at %s couldn't be opened\n", path.c_str());
        return { .vertexShader = "", .fragmentShader = "" };
    }

    std::string vertexShader;
    std::string fragmentShader;
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)) {
        line.append("\n");
        if (line.find("# vertex") != std::string::npos) {
            // we are reading the vertex shader
            type = ShaderType::VERTEX;
            continue;
        }
        if (line.find("# fragment") != std::string::npos) {
            // we are reading the vertex shader
            type = ShaderType::FRAGMENT;
            continue;
        }
        switch (type) {
            case ShaderType::VERTEX:
                vertexShader.append(line);
                break;
            case ShaderType::FRAGMENT:
                fragmentShader.append(line);
                break;
            default:
                break;
        }
    }

    stream.close();

    return { .vertexShader = vertexShader, .fragmentShader = fragmentShader };
}

unsigned int compileShader(const std::string &source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str(); // convert source to c-string
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // to get some errors while compiling the shader
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << message << std::endl;
    }

    return id;
}

unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
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
    window = glfwCreateWindow(800, 500, "Error handling", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Window couldn't be created.");
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
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

    // allocate the VAO and get the ID
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // allocate VBO and get the ID
    auto vertexBuffer = VertexBuffer(&vertices, sizeof(vertices));
    // specifying the buffer layout
    // position layout
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // index buffer
//    unsigned int iao;
//    glGenBuffers(1, &iao);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iao);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    auto indexBuffer = IndexBuffer(indices, 6);

    auto shaders = readShaders("shader.glsl");
    unsigned int shader = createShader(shaders.vertexShader, shaders.fragmentShader);
    glUseProgram(shader);

    float b = 1;
    float increment = 0.1;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(int location = glGetUniformLocation(shader, "u_color"));
        GLCall(glUniform4f(location, 1.0, 0.4, b, 1));
//        indexBuffer.bind();
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