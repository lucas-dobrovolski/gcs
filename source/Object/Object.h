// Object.h
#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace GSC {
class Object {
    public:
    glm::mat4 transform;
    std::shared_ptr<Mesh> mesh;

    Object();                           // solo declaración
    Object(std::shared_ptr<Mesh> m);    // solo declaración

    void setTransform(const glm::mat4& t);
    const glm::mat4& getTransform() const;

    void setMesh(std::shared_ptr<Mesh> m);
    
    std::shared_ptr<Mesh> getMesh();
};
}