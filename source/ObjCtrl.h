#pragma once

#include <vector>
#include <memory>
#include "ext/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "gsc.h"

namespace GSC {

class ObjCtrl { 


    public:
        std::vector<std::unique_ptr<Object>> objects;
        
        ObjCtrl();    
        ~ObjCtrl();    
        
        void addObject(Object obj);
        void setCoreObjects();
        void setObjTransf();
        Object getObjTransf(int i);
        glm::mat4 getUpdatedModel();
    };
    
class Object {
    public:
    Object();
    virtual ~Object();

    glm::mat4 coords = glm::mat4(1.0);

    bool visible = true;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint indexCounts;


    std::vector<float> verts;
    std::vector<unsigned int> verts_index;
    


};



class Icosahedron : public Object {  // Faltaba "public"
    public:
    Icosahedron() {
        
        const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;
        
        // 12 vértices del icosaedro
        verts = {
            -1,  t,  0,   1,  t,  0,   -1, -t,  0,   1, -t,  0,
             0, -1,  t,   0,  1,  t,    0, -1, -t,   0,  1, -t,
             t,  0, -1,   t,  0,  1,   -t,  0, -1,  -t,  0,  1
        };
        
        // 20 caras triangulares
        verts_index = {
            0, 11, 5,   0, 5, 1,   0, 1, 7,   0, 7, 10,  0, 10, 11,
            1, 5, 9,    5, 11, 4,  11, 10, 2, 10, 7, 6,  7, 1, 8,
            3, 9, 4,    3, 4, 2,   3, 2, 6,   3, 6, 8,   3, 8, 9,
            4, 9, 5,    2, 4, 11,  6, 2, 10,  8, 6, 7,   9, 8, 1
        };
        
        indexCounts = verts_index.size();
        }
    }

private:
    void createIcosahedron() {

        // N aureo
};
}






}