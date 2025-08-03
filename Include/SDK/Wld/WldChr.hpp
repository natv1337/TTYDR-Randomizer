#pragma once

#include "../../Util.hpp"

namespace wld::chr {

class Manager {
public:
    virtual ~Manager();
    virtual void Deleter();
    virtual void Vfunc3();
    virtual void Vfunc4();
    virtual void Vfunc5(void*);
    virtual void Vfunc6();
    virtual void Vfunc7();
    virtual bool Vfunc8(void*);
    virtual bool Vfunc9(void*);

private:
    char pad_0008[0x18];

};
ASSERT_SIZE(Manager, 0x20);

}