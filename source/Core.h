//# Core.h
#pragma once
#include <memory>


#include "LgcCtrl.h"
#include "WinCtrl.h"
#include "GPUCtrl.h"
#include "ObjCtrl.h"
#include "IptCtrl.h"
#include "UICtrl.h"

#include "gcs.h"

namespace GCS {

class Core {
    
    private:
    
            std::unique_ptr<LgcCtrl>        lgcCtrl;
            std::unique_ptr<WinCtrl>        winCtrl;
            std::unique_ptr<GPUCtrl>        gpuCtrl;
            std::unique_ptr<ObjCtrl>        objCtrl;
            std::unique_ptr<IptCtrl>        iptCtrl;
             std::unique_ptr<UICtrl>        uiCtrl;

    public:

            Core();
            ~Core();

            void GO();
            void BYE();
};









}