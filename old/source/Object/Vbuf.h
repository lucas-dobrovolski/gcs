// Mesh.h
#pragma once

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace GSC {
    ///////////////////////////////////////////////////////////////
class Vbuf {
public:
    GLuint vao, vbo, ebo;
    GLsizei indexCount;

    Vbuf(GLuint vao_, GLuint vbo_, GLuint ebo_, GLsizei count);
};
//////////////////////////////////////////////////////////////


} // namespace GSC
