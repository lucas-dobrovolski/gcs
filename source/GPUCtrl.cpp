#include "GPUCtrl.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
GSC::GPUCtrl::GPUCtrl(){


    GSC::log("|◉|◉| GPUctrl ok");
}

//destructor
GSC::GPUCtrl::~GPUCtrl() {
    // Borrar todos los shaders
    for (GLuint prog : shaderPrograms) {
        glDeleteProgram(prog);
    }

    // Borrar todos los VAOs
    for (GLuint vao : vaoList) {
        glDeleteVertexArrays(1, &vao);
    }

    // Borrar todos los VBOs
    for (GLuint vbo : vboList) {
        glDeleteBuffers(1, &vbo);
    }

    // Borrar todos los EBOs
    for (GLuint ebo : eboList) {
        glDeleteBuffers(1, &ebo);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////



GLuint GSC::GPUCtrl::getShader(int i){
    return shaderPrograms[i];
}



void GSC::GPUCtrl::setGladContext(){
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        GSC::log("|◉|X| GPUctrl GLAD INIT FAILED");
    return;
    }
    else { GSC::log("|◉|◉| GPUctrl init glad ok"); }

    
}



void GSC::GPUCtrl::readCoreShader(){

GSC::log("|◉|◌| GPUctrl reading core shaders");

static const char* ver_code = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform mat4 M;
    uniform mat4 V;
    uniform mat4 P;

    void main() {
        gl_Position = P * V * M * vec4(aPos, 1.0);
    }
    )";
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &ver_code, nullptr);
        glCompileShader(vs);
        
static const char* fra_src = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4({1.0,1.0,1.0,1.0}); // blanco
        }
        )";
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fra_src, nullptr);
    glCompileShader(fs);
    //////////////////////////////////
    GLuint coreShader = glCreateProgram();
                                        glAttachShader(coreShader, vs);
                                        glAttachShader(coreShader, fs);
                                        glLinkProgram(coreShader);
                                        
                                        glDeleteShader(vs);
                                        glDeleteShader(fs);
                                        shaderPrograms.push_back    (coreShader);
 
                                        GSC::log("|◉|◉| GPUctrl shaders ready");
}


void GSC::GPUCtrl::setCoreVO(){
GSC::log("|◉|◌| GPUctrl setting core VO");
    static const float t = 1.61803398875f;
    static const float icoVerts[] = {
    -1,  t,  0,
    1,  t,  0,
    -1, -t,  0,
    1, -t,  0,

    0, -1,  t,
    0,  1,  t,
    0, -1, -t,
    0,  1, -t,

    t,  0, -1,
    t,  0,  1,
    -t,  0, -1,
    -t,  0,  1
    };

    static const unsigned int icoIndex[] = {
    0, 11, 5,
    0, 5,  1,
    0, 1,  7,
    0, 7, 10,
    0, 10, 11,

    1, 5,  9,
    5, 11, 4,
    11,10, 2,
    10,7,  6,
    7, 1,  8,

    3, 9,  4,
    3, 4,  2,
    3, 2,  6,
    3, 6,  8,
    3, 8,  9,

    4, 9,  5,
    2, 4, 11,
    6, 2, 10,
    8, 6,  7,
    9, 8,  1
    };

    indexCounts.push_back(sizeof(icoIndex) / sizeof(icoIndex[0]));

    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(icoVerts), icoVerts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(icoIndex), icoIndex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vaoList.push_back(vao);
    vboList.push_back(vbo);
    eboList.push_back(ebo);

}


void GSC::GPUCtrl::useShader(int i){
    glUseProgram(shaderPrograms[i]);
}


void GSC::GPUCtrl::drawBuffer(int i){
    GSC::log("|◉|◌| GPUctrl  drawing from vao list");
    glBindVertexArray(vaoList[i]);
        GSC::log("|◉|◌| GPUctrl  drawing from vao list");
    glDrawElements(GL_TRIANGLES, indexCounts[i], GL_UNSIGNED_INT, 0);
    GSC::log("|◉|◉| GPUctrl buffer showed ");

}


/*
|◉|◌| GPUctrl setting core VO
|◉|◌| GPUctrl  drawing from vao list
Violación de segmento (`core' generado)
lambda@lambda-Desk:~/dev/gcs$ 
*/