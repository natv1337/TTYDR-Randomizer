/**
 * @file Math.hpp
 * @brief Class definitions for the math namespace.
 */
#pragma once

#include "../Util.hpp"

namespace math {

struct Vec2 {
    float x, y;
};
ASSERT_SIZE(Vec2, 8);

struct Vec3 {
    float x, y, z;
private:
    char pad_000C[4];
};
ASSERT_SIZE(Vec3, 0x10);
    
struct Vec4 {
    float x, y, z, w;
};
ASSERT_SIZE(Vec4, 0x10);

struct Mtx43 {
    Vec4 x, y, z;
};
ASSERT_SIZE(Mtx43, 0x30);

struct Mtx44 {
    Vec4 x, y, z, w;
};
ASSERT_SIZE(Mtx44, 0x40);

} // namespace math