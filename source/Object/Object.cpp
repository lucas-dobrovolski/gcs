// Object.cpp
#include "Object.h"


GSC::Object::Object(){}

void GSC::Object::setTransform(const glm::mat4& t) {
    transform = t;
}

const glm::mat4& GSC::Object::getTransform() const {
    return transform;
}

void GSC::Object::setMesh(std::shared_ptr<Mesh> m) {
    mesh = std::move(m);
}

std::shared_ptr<GSC::Mesh> GSC::Object::getMesh(){
    return mesh;
}
