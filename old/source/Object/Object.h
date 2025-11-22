// Object.h
#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "Vbuf.h"

namespace GSC {
class Object {
    public:
    glm::mat4 transform;
    std::shared_ptr<Vbuf> buffer;

    Object();                           // solo declaración
    Object(std::shared_ptr<Vbuf> m);    // solo declaración

    void setTransform(const glm::mat4& t);
    const glm::mat4& getTransform() const;

    void setVbuf(std::shared_ptr<Vbuf> m);
    std::shared_ptr<Vbuf> getVbuf()const;
};
}