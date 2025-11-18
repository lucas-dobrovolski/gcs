#include "Core.h"


GSC::Core::Core()
{
    GSC::log("|◌| Core awake");
    lgc = std::make_unique<LgcCtrl>();
    win = std::make_unique<WinCtrl>();
    gpu = std::make_unique<GPUCtrl>();   
    
    GSC::log("|◉| Core ready ");
}
GSC::Core::~Core(){}

void GSC::Core::GO(){
    
    
    GSC::log("|◌| Core START");
    
    win->initCoreWin();

    gpu->setGladContext();
    
    lgc->set();
    
    gpu->readCoreShader();
    gpu->setCoreVO();
   
        GSC::log("|◌| Core WHILE");
       
        while (!glfwWindowShouldClose(win->getCoreWin())) {
            
            lgc->run();
            
            win->clearWindow();

            gpu->setCoreVO();
            gpu->useShader(0);
            gpu->drawBuffer(0);
            
            win->pollWindow();
            
            }

    GSC::log("|◌| Core REST");
    
    //    6. Cleanup crudo
    


   

    /*
    */
   GSC::log("|✓| Core: END");
   
}

