// Mesh.h
#pragma once

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace GSC {
    ///////////////////////////////////////////////////////////////
class Mesh {
public:
    GLuint vao, vbo, ebo;
    GLsizei indexCount;

    Mesh() = default; // mesh vacía, opcional

    Mesh(GLuint vao_, GLuint vbo_, GLuint ebo_, GLsizei count);
};
//////////////////////////////////////////////////////////////


} // namespace GSC
