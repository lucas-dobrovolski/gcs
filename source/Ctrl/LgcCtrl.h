#pragma once
#include <chrono>
#include <ctime>
#include "gsc.h"
namespace GSC {

class LgcCtrl {    public:
        
        
        LgcCtrl();
        ~LgcCtrl();
        
        void set();
        void run();
        
        uint64_t evaluate_t_us();
};






}