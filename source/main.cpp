#include <iostream>

#include "Core.h"

#include "gsc.h"

int main(){

    GSC::log("~main~~~~~~~~~~~~~~~~");
    GSC::log("main -> onEntryPoint");
    bool onEntryPoint = true;
    

    while(onEntryPoint){

        GSC::log("~main->While~~~~");

        GSC::log("main -> NEW CORE ");
        GSC::Core CORE;

        GSC::log("main -> CORE GO ");    
        CORE.GO();
        GSC::log(" CORE END -> main ");
        

        GSC::log("~main->While~~~~WAITING~TO~RESTART~");
        GSC::log("main -> PRESS Q TO QUIT");
        GSC::log("main -> PRESS ENTER TO RE RUN");
        int c = std::cin.get();
        if (c == 'q') { onEntryPoint = false; GSC::log("main -> Q: QUIT"); return 0;}
        else { GSC::log("main -> restart"); }

    }
}