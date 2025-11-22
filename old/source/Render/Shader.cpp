#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace GSC {

// ---------------------------------------------------------
// Helpers
// ---------------------------------------------------------

std::string Shader::loadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "[Shader] No se pudo abrir el archivo: " << path << "\n";
        return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

GLuint Shader::compile(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "[Shader] Error compilando shader "
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << ":\n" << log << "\n";
    }

    return shader;
}

GLint Shader::uniformLoc(const char* name) const {
    return glGetUniformLocation(program, name);
}

// ---------------------------------------------------------
// Constructors
// ---------------------------------------------------------

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    GLuint vs = compile(GL_VERTEX_SHADER, vertexSrc);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fragmentSrc);

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        std::cerr << "[Shader] Error linkeando programa:\n" << log << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string v = loadFile(vertexPath);
    std::string f = loadFile(fragmentPath);

    GLuint vs = compile(GL_VERTEX_SHADER, v.c_str());
    GLuint fs = compile(GL_FRAGMENT_SHADER, f.c_str());

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        std::cerr << "[Shader] Error linkeando programa:\n" << log << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------

Shader::~Shader() {
    if (program != 0)
        glDeleteProgram(program);
}

// ---------------------------------------------------------
// API
// ---------------------------------------------------------

void Shader::use() const {
    glUseProgram(program);
}

void Shader::setMat4(const char* name, const glm::mat4& value) const {
    glUniformMatrix4fv(uniformLoc(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setVec3(const char* name, const glm::vec3& value) const {
    glUniform3fv(uniformLoc(name), 1, &value[0]);
}

void Shader::setFloat(const char* name, float value) const {
    glUniform1f(uniformLoc(name), value);
}

void Shader::setInt(const char* name, int value) const {
    glUniform1i(uniformLoc(name), value);
}

} // namespace GSC
