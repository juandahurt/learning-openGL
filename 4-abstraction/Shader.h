//
// Created by Juan Hurtado on 18/03/24.
//

#ifndef INC_4_ABSTRACTION_SHADER_H
#define INC_4_ABSTRACTION_SHADER_H

#include <fstream>
#include <iostream>
#include "Renderer.h"

struct ShadersSource {
    std::string vertexShader;
    std::string fragmentShader;
};
enum ShaderType {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

class Shader {
private:
    unsigned int m_shaderId;
    std::string m_filepath;
    ShadersSource _readShader();
    int _createShader(const std::string &vertexShader, const std::string &fragmentShader);
    unsigned int _compileShader(const std::string &source, unsigned int type);
public:
    Shader(const std::string &path);
    ~Shader();
    void bind();

    template<typename T>
    void uniform4(const std::string &name, T v0, T v1, T v2, T v3) {}

    template<>
    void uniform4<float>(const std::string &name, float v0, float v1, float v2, float v3) {
        GLCall(int location = glGetUniformLocation(m_shaderId, name.c_str()));
        if (location < 0) {
            std::cout << "Uniform not found" << std::endl;
        }
        GLCall(glUniform4f(location, v0, v1, v2 ,v3));
    }
};


#endif //INC_4_ABSTRACTION_SHADER_H
