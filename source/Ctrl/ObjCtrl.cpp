// ObjCtrl.cpp
#include "ObjCtrl.h"

namespace GSC {

void ObjCtrl::addObject(const std::shared_ptr<Object>& obj) {
    objects.push_back(obj);
}

const std::vector<std::shared_ptr<Object>>& ObjCtrl::getObjects() const {
    return objects;
}

} // namespace GSC
