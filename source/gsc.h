#pragma once

#include <iostream>
#include <glm/glm.hpp>                // tipos básicos: vec3, mat4
#include <glm/gtc/matrix_transform.hpp> // funciones de transformación: translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>        // glm::value_ptr

namespace GSC {

    void log(const char* msg);
    
    // vertices "obj"
    struct Transform {
    glm::vec3 position = glm::vec3(0.0f); // centro del mundo
    glm::vec3 rotation = glm::vec3(0.0f); // sin rotación
    glm::vec3 scale    = glm::vec3(1.0f); // tamaño original
    };
}