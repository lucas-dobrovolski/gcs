
/////////////////////////////////////////////////////////////////////////
// ObjCtrl.h
#pragma once
#include <vector>
#include <memory>

#include "../Object/Vbuf.h"
#include "../Object/Object.h"

namespace GSC {

class ObjCtrl {
public:
    std::vector<std::shared_ptr<Object>> objects;

public:
    ObjCtrl() = default;
    ~ObjCtrl() = default;

    void addObject(const std::shared_ptr<Object>& obj);
    const std::vector<std::shared_ptr<Object>>& getObjects() const;
};

} // namespace GSC
