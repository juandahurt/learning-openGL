//
// Created by Juan Hurtado on 18/03/24.
//

#include "Shader.h"

Shader::Shader(const std::string &path) {
    m_filepath = path;
    auto sources = _readShader();
    m_shaderId = _createShader(sources.vertexShader, sources.fragmentShader);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_shaderId));
}

unsigned int Shader::_compileShader(const std::string &source, unsigned int type) {
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

int Shader::_createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = _compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = _compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShadersSource Shader::_readShader() {
    std::ifstream stream(m_filepath);
    std::string line;

    if (!stream.is_open()) {
        fprintf(stderr, "ERROR: file at %s couldn't be opened\n", m_filepath.c_str());
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

void Shader::bind() {
    glUseProgram(m_shaderId);
}