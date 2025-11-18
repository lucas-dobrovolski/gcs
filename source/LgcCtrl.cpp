#include "LgcCtrl.h"

GSC::LgcCtrl::LgcCtrl(){
    
        

    GSC::log("|◉|◉| Lgcctrl ok");
}
GSC::LgcCtrl::~LgcCtrl(){}

void GSC::LgcCtrl::set(){

    Transform isocaedro;
    isocaedro.position = glm::vec3(0.0f, 0.0f, 0.0f); // mover hacia arriba y alejar
    isocaedro.rotation = glm::vec3(45.0f, 30.0f, 0.0f); // rotar 45° X, 30° Y
    isocaedro.scale    = glm::vec3(0.5f); // reducir a la mitad

}

void GSC::LgcCtrl::run(){


}