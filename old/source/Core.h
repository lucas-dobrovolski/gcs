#pragma once
//# Core.h
#include <memory>

#include "Ctrl/LgcCtrl.h"
#include "Ctrl/WinCtrl.h"
#include "Ctrl/GPUCtrl.h"
#include "Ctrl/ObjCtrl.h"

#include "gsc.h"

namespace GSC {

class Core {

    private:
    
            std::unique_ptr<LgcCtrl>        lgc;
            std::unique_ptr<WinCtrl>        win;
            std::unique_ptr<GPUCtrl>        gpu;
            std::unique_ptr<ObjCtrl>        obj;
            //std::unique_ptr<IptCtrl>        ipt;
            // std::unique_ptr<UICtrl>        ui;

    public:

            Core();
            ~Core();

            void GO();
        }; 

}