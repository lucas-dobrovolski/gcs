#pragma once

#include <iostream>

namespace GCS {

    inline void log(const char* msg){
        std::cout << msg << "\n";
    }
}