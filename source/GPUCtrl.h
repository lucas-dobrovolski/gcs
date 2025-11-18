#pragma once
#include <vector>
#include "ext/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "ObjCtrl.h"

#include "gsc.h"

namespace GSC {

    class GPUCtrl {

        private:


            GLuint shaderProgram = 0;

            std::vector<GLuint> shaderPrograms;

            std::vector<GLuint> vaoList;
            std::vector<GLuint> indexCounts; // paralelo a vaoList
            std::vector<GLuint> vboList;
            std::vector<GLuint> eboList;

        public:

            GPUCtrl();
            ~GPUCtrl();       

            GLuint getShader(int i);
            void setGladContext();

            void readCoreShader();
            void setCoreVO();

            void useShader(int i);
            void drawBuffer(int i);
    };
}