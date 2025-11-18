#include "GPUCtrl.h"



namespace GSC {
}
//constructor
GSC::GPUCtrl::GPUCtrl(){


    shaderList.push_back(R"(
#version 330 core

layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)");


    shaderList.push_back(R"(
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0); // blanco
}
)");

//destructor
}
GSC::GPUCtrl::~GPUCtrl(){
}

const GLchar* GSC::GPUCtrl::getShader(int i){
            return shaderList[i];
        }