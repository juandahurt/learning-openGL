//
// Created by Juan Hurtado on 8/03/24.
//

#ifndef LEARNING_OPENGL_SHADER_FROM_FILE_H
#define LEARNING_OPENGL_SHADER_FROM_FILE_H


#include <fstream>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../example.h"

class ShaderFromFile: example {
    struct ShadersSource {
        std::string vertexShader;
        std::string fragmentShader;
    };
    enum ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
public:
    ShadersSource readShaders(const std::string &path) {
        std::ifstream stream(path);
        std::string line;

        if (!stream.is_open()) {
            fprintf(stderr, "ERROR: file at %s couldn't be opened", path.c_str());
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

    void setupTriangle() {
        float vertices[] = {
                0, 1,
                1, -1,
                -1, -1,
        };

        // allocate the VAO and get the ID
        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // allocate VBO and get the ID
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // specifying the buffer layout
        // position layout
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);


        auto shaders = readShaders("src/2-shader-from-file/shader.glsl");
        unsigned int shader = createShader(shaders.vertexShader, shaders.fragmentShader);
        glUseProgram(shader);
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

    int run() {
        GLFWwindow *window;

        if (!glfwInit()) {
            fprintf(stderr, "GLEW couldn't be initialized!\n");
            return -1;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        window = glfwCreateWindow(800, 500, "Shader from file", nullptr, nullptr);
        if (!window) {
            fprintf(stderr, "Window couldn't be created.");
            return -1;
        }
        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "GLEW couldn't be initialized!\n");
            return -1;
        }

        setupTriangle();
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();

        return 0;
    }
};

#endif //LEARNING_OPENGL_SHADER_FROM_FILE_H
