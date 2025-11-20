#include "Mesh.h"

GSC::Mesh::Mesh(GLuint vao_, GLuint vbo_, GLuint ebo_, GLsizei count)
    : vao(vao_), vbo(vbo_), ebo(ebo_), indexCount(count)
{}
