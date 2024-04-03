//
// Created by Juan Hurtado on 25/03/24.
//

#ifndef INC_6_PERSPECTIVE_SHADER_H
#define INC_6_PERSPECTIVE_SHADER_H

#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
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
    int _getUniformLocation(const std::string& name);
public:
    Shader(const std::string &path);
    ~Shader();
    void bind();

    template<typename T>
    void uniform4(const std::string &name, T v0, T v1, T v2, T v3) {}

    template<>
    void uniform4<float>(const std::string &name, float v0, float v1, float v2, float v3) {
        int location = _getUniformLocation(name);
        GLCall(glUniform4f(location, v0, v1, v2 ,v3));
    }

    // this could also use generics, but I didn't really want to spend more time on this, so yeah...
    void uniform1i(const std::string& name, int value) {
        int location = _getUniformLocation(name);
        GLCall(glUniform1i(location, value));
    }

    void uniformMat4f(const std::string& name, glm::mat4& matrix) {
        int location = _getUniformLocation(name);
        GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
    }
};


#endif //INC_6_PERSPECTIVE_SHADER_H
