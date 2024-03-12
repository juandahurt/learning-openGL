//
// Created by Juan Hurtado on 8/03/24.
//

#ifndef LEARNING_OPENGL_HELLO_WORLD_H
#define LEARNING_OPENGL_HELLO_WORLD_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../example.h"


class HelloWorld: Example {
    unsigned int vbo[1]; // vertex buffer object
    unsigned int vao[1]; // vertex array object

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

    void setupTriangle() {
        float vertices[] = {
                0, 1, 1, 0, 0, // x y r g b
                1, -1, 0, 1, 0,
                -1, -1, 0, 0, 1
        };

        // allocate the VAO and get the ID
        glGenVertexArrays(1, &vao[0]);
        glBindVertexArray(vao[0]);

        // allocate VBO and get the ID
        glGenBuffers(1, &vbo[0]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // specifying the buffer layout
        // position layout
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        // color layout
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        // create the shaders
        const std::string vertexShader = "#version 330 core\n"
                                         "\n"
                                         "layout(location=0) in vec3 vertPos;\n"
                                         "layout(location=1) in vec3 color; // r,b,g\n"
                                         "out vec3 theColor; // out = output\n"
                                         "\n"
                                         "void main() {\n"
                                         "   gl_Position = vec4(vertPos.x, vertPos.y, 0, 1);\n"
                                         "   theColor = color;"
                                         "}\n";

        const std::string fragmentShader = "#version 330 core\n"
                                           "\n"
                                           "in vec3 theColor;\n"
                                           "out vec4 pixelColor;\n"
                                           "\n"
                                           "void main() {\n"
                                           "   pixelColor = vec4(theColor, 1);\n"
                                           "}\n";
        unsigned int shader = createShader(vertexShader, fragmentShader);
        glUseProgram(shader);
    }
public:
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
        window = glfwCreateWindow(800, 500, "Hello world!", nullptr, nullptr);
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

#endif //LEARNING_OPENGL_HELLO_WORLD_H
