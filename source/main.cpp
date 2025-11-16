#include <iostream>

#include "Core.h"

#include "gcs.h"

int main(){
    GCS::log("\n~main~~~~~~~~~~~~~~~~");
    GCS::log("main -> onEntryPoint");
    bool onEntryPoint = true;
    
    while(onEntryPoint){
        GCS::log("\n~main->While~~~~");
        GCS::log("main -> NEW CORE ");
        GCS::Core CORE;
        GCS::log("main -> CORE GO ");    
        CORE.GO();
        GCS::log("main -> CORE END ");
        
        GCS::log("\n~main->While~~~~WAITING~TO~RESTART~");
        GCS::log("main -> PRESS Q TO QUIT");
        GCS::log("main -> PRESS ENTER TO RE RUN");
        int c = std::cin.get();
        if (c == 'q') { onEntryPoint = false; GCS::log("main -> Q: QUIT"); return 0;}
        else { GCS::log("main -> restart"); }
    }
}