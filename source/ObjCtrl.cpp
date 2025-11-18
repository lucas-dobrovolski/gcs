#include "ObjCtrl.h"
GSC::ObjCtrl::ObjCtrl(){

}

GSC::ObjCtrl::~ObjCtrl(){

}

void GSC::ObjCtrl::setCoreObjects(){
    objects.push_back(std::make_unique<Object>());
}

GSC::ObjCtrl::Icosahedron : GSC::ObjCtrl::Object(){
    
}