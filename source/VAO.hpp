
#include <glad/glad.h>  
#include <vector>
#include "common.hpp"

struct VAO {
private:
    GLuint ID;
    GLuint VBO = 0;
    GLuint EBO = 0;

public:
    VAO() {
        glGenVertexArrays(1, &ID);
        glBindVertexArray(ID);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    ~VAO() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &ID);
    }

    void bind() const { glBindVertexArray(ID); }
    void unbind() const { glBindVertexArray(0); }

    void setVertexData(const std::vector<Vertex>& vec, GLenum usage = GL_STATIC_DRAW) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(Vertex), vec.data(), usage);
    }

    void setIndexData(const std::vector<unsigned int>& vec, GLenum usage = GL_STATIC_DRAW) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vec.size() * sizeof(unsigned int), vec.data(), usage);
    }

    void addAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized,
                   GLsizei stride, const void* offset) const {
                       /* Agrega un atributo de vertice. 
                       index:       ubicacion del atrib en shader: 0, 1, 2...
                       size:        cantidad de componentes (3 para vec3, 2 para vec2)
                       type:        tipo de dato (GL_FLOAT, etc.)
                       normalized:  si los datos deben normalizarse
                       stride:      tamaño total del vértice (sizeof(Vertex))
                       offset:      desplazamiento dentro del vértice xej " (offsetof(Vertex, normal)) ""*/
                       glEnableVertexAttribArray(index);
                       glVertexAttribPointer(index, size, type, normalized, stride, offset);
    }
};
