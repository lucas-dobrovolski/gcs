#include "GPUCtrl.h"
using namespace GSC;

GPUCtrl::GPUCtrl() {}

GPUCtrl::~GPUCtrl() {
    // Nada que borrar manualmente.
    // Al destruirse este vector, los shared_ptr eliminarán sus Shader,
    // y cada Shader destruye su propio glDeleteProgram().
}

void GPUCtrl::setGladContext() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Error iniciando GLAD");
    }
}

std::shared_ptr<Shader> GPUCtrl::makeShader(const char* vs, const char* fs) {
    auto shader = std::make_shared<Shader>(vs, fs);
    shaders.push_back(shader);
    return shader;
}

std::shared_ptr<Vbuf> GPUCtrl::VbufFromGeometry(const Geometry& geo) {
    auto vert_buffer = std::make_shared<Vbuf>();

    glGenVertexArrays(1, &vert_buffer->vao);
    glGenBuffers(1, &vert_buffer->vbo);
    glGenBuffers(1, &vert_buffer->ebo);

    glBindVertexArray(vert_buffer->vao);

    glBindBuffer(GL_ARRAY_BUFFER, vert_buffer->vbo);
    glBufferData(GL_ARRAY_BUFFER, geo.vertices.size() * sizeof(glm::vec3),
                 geo.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vert_buffer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, geo.indices.size() * sizeof(unsigned),
                 geo.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    vert_buffer->indexCount = geo.indices.size();
    return vert_buffer;
}

void GPUCtrl::renderObj(const ObjCtrl& objCtrl, Shader& shader) {

    glUseProgram(shader.getProgram());

    GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");

    for (auto& obj : objCtrl.getObjects()) {
        if (!obj->buffer) continue;

        glBindVertexArray(obj->buffer->vao);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &obj->transform[0][0]);

        glDrawElements(GL_TRIANGLES,
                       obj->buffer->indexCount,
                       GL_UNSIGNED_INT, 0);
    }
}
