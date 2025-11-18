#include "LgcCtrl.h"

GSC::LgcCtrl::LgcCtrl(){
    
        

    GSC::log("|◉|◉| Lgcctrl ok");
}
GSC::LgcCtrl::~LgcCtrl(){}

void GSC::LgcCtrl::set(){


}

void GSC::LgcCtrl::run(){


}


uint64_t GSC::LgcCtrl::evaluate_t_us()
{
    // tiempo actual desde epoch
    auto now = std::chrono::high_resolution_clock::now();

    // convertir a microsegundos desde epoch
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());

    return us.count(); // devuelve el valor como entero de 64 bits
}

