#include "gsc.h"

namespace GSC{



void log(const char* msg){
        std::cout << msg << "\n";
    }


std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::cout << path << std::endl;
    if (!file.is_open()) {
        throw std::runtime_error("No pude abrir " + path);
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}


}