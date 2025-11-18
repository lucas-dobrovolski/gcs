#pragma once

#include <iostream>

namespace GSC {

    inline void log(const char* msg){
        std::cout << msg << "\n";
    }
}