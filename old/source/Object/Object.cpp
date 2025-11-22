// Object.cpp
#include "Object.h"


GSC::Object::Object(){}

void GSC::Object::setTransform(const glm::mat4& t) {
    transform = t;
}

const glm::mat4& GSC::Object::getTransform() const {
    return transform;
}

void GSC::Object::setVbuf(std::shared_ptr<Vbuf> m) {
    buffer = std::move(m);
}

std::shared_ptr<GSC::Vbuf> GSC::Object::getVbuf() const {
    return buffer;
}
