#pragma once
//# Core.h
#include <memory>

#include "LgcCtrl.h"
#include "WinCtrl.h"
#include "GPUCtrl.h"


#include "gsc.h"

namespace GSC {

class Core {

    private:
    
            std::unique_ptr<LgcCtrl>        lgc;
            std::unique_ptr<WinCtrl>        win;
            std::unique_ptr<GPUCtrl>        gpu;
            //std::unique_ptr<ObjCtrl>        objCtrl;
            //std::unique_ptr<IptCtrl>        iptCtrl;
            // std::unique_ptr<UICtrl>        uiCtrl;

    public:

            Core(

            );
            ~Core();

            void GO();
        }; 

}