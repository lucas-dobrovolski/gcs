#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace GSC {

struct Geometry {
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    static Geometry makeCube(float size);
};

} // namespace GSC
