#pragma once

namespace collision {

namespace hit {

class ShapeObjCtrl {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    virtual void vfunc3();
    virtual void vfunc4();
    virtual void vfunc5();
    virtual void vfunc6();
    virtual void vfunc7();
};

class ShapeObjManager {
public:
    virtual ~ShapeObjManager();

private:
    char pad_0008[0xC8];

};
static_assert(sizeof(ShapeObjManager) == 0xD0);

}

} // namespace collision