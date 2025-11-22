#pragma once
#include <glm/glm.hpp>
#include <iostream>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

inline void logmsg(const char* msg) {
    std::cout << " ◉ " << msg << "\n";
}
