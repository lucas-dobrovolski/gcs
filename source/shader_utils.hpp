#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>  
#include <GLFW/glfw3.h> 

#include "common.hpp"

inline std::string readFile(const char* path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        logmsg("ERROR: READ FILE");
        std::cerr << "No pude abrir " << path << "\n";
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

inline GLuint compileShader(const char* path, GLenum type) {
    std::string src = readFile(path);
    if (src.empty()) return 0;

    GLuint shader = glCreateShader(type);
    const char* csrc = src.c_str();

    glShaderSource(shader, 1, &csrc, nullptr);
    glCompileShader(shader);

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);

    if (!ok) {
        GLint len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

        std::string log(len, '\0');
        glGetShaderInfoLog(shader, len, nullptr, &log[0]);
        logmsg("ERROR: COMPILE SHADER");
        std::cerr << "Error compilando " << path << ":\n"
                    << log << "\n";

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

inline GLuint makeProgram(const char* vpath, const char* fpath) {
    GLuint vs = compileShader(vpath, GL_VERTEX_SHADER);
    GLuint fs = compileShader(fpath, GL_FRAGMENT_SHADER);

    if (!vs || !fs) {
        logmsg("ERROR: MAKE PROGRAM");
        std::cerr << "No se pudieron compilar los shaders\n";
        return 0;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    GLint ok;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);

    if (!ok) {
        GLint len;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

        std::string log(len, '\0');
        glGetProgramInfoLog(prog, len, nullptr, &log[0]);
        logmsg("ERROR: MAKE PROGRAM");
        std::cerr << "Error linkeando programa:\n"
                    << log << "\n";

        glDeleteProgram(prog);
        prog = 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}

