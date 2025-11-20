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

std::shared_ptr<Mesh> GPUCtrl::uploadGeometry(const Geometry& geo) {
    auto mesh = std::make_shared<Mesh>();

    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);

    glBindVertexArray(mesh->vao);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, geo.vertices.size() * sizeof(glm::vec3),
                 geo.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, geo.indices.size() * sizeof(unsigned),
                 geo.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    mesh->indexCount = geo.indices.size();
    return mesh;
}

void GPUCtrl::render(const ObjCtrl& objCtrl, Shader& shader) {

    glUseProgram(shader.getProgram());

    GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");

    for (auto& obj : objCtrl.getObjects()) {
        if (!obj->mesh) continue;

        glBindVertexArray(obj->mesh->vao);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &obj->transform[0][0]);

        glDrawElements(GL_TRIANGLES,
                       obj->mesh->indexCount,
                       GL_UNSIGNED_INT, 0);
    }
}
