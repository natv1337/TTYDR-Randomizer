/**
 * @file Collision.hpp
 * @brief Class definitions for the collision namespace.
 */
#pragma once

#include "../Util.hpp"

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
ASSERT_SIZE(ShapeObjCtrl, 0x08);

class ShapeObjManager {
public:
    virtual ~ShapeObjManager();

private:
    char pad_0008[0xC8];

};
ASSERT_SIZE(ShapeObjManager, 0xD0);

}

} // namespace collision