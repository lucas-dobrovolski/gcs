#pragma once
#include <vector>
#include "ext/glad/include/glad/glad.h"


namespace GSC {

class GPUCtrl {

    private:

        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int shaderProgram = 0;

        std::vector<const char*> shaderList;

    public:

        GPUCtrl();
        ~GPUCtrl();       

        const GLchar* getShader(int i);

};



}

// error
// a member with an in-class initializer must be constC/C++(1592)