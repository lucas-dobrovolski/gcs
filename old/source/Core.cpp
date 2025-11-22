#include "Core.h"


GSC::Core::Core()
{
    GSC::log("|◌| Core awake");
    lgc = std::make_unique<LgcCtrl>();
    win = std::make_unique<WinCtrl>();
    gpu = std::make_unique<GPUCtrl>();   
    obj = std::make_unique<ObjCtrl>();
    GSC::log("|◉| Core ready ");
}
GSC::Core::~Core(){}

void GSC::Core::GO(){
    
    
    GSC::log("|◌| Core START");
    
    win->initCoreWin();

    gpu->setGladContext();
    

    auto geo = GSC::Geometry::makeCube(1.0f);
    
    auto Vbuf = gpu->VbufFromGeometry(geo);

    auto cubo = std::make_shared<Object>();

    Object cube;
    cube.setVbuf(Vbuf);
    cube.setTransform(glm::mat4(1.0f));

    obj->addObject(cubo);
    
    // proyección
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        400.0f / 400.0f,
        0.1f, 100.0f
    );

    // vista (cámara)
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    std::string vsText = readFile("shaders/basic.vert");
    std::string fsText = readFile("shaders/basic.frag");

    auto shader = gpu->makeShader(vsText.c_str(), fsText.c_str());

    GSC::log("|◌| Core WHILE");
       
    while (!glfwWindowShouldClose(win->getCoreWin())) {
        float angle = (float)glfwGetTime() * 0.01; 
        cube.transform = glm::rotate(cube.transform, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        win->clearWindow();

        shader->use();
        shader->setMat4("model", cube.transform);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);

        glBindVertexArray(cube.buffer->vao);
        glDrawElements(GL_TRIANGLES, cube.buffer->indexCount, GL_UNSIGNED_INT, 0);

        win->pollWindow();
        
        }

    GSC::log("|◌| Core REST");

   GSC::log("|✓| Core: END");
   
}



