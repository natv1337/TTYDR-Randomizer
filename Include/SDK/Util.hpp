/**
 * @file Util.hpp
 * @brief Class definitions for the util namespace.
 */
#pragma once

#include "../Util.hpp"

namespace util {

struct Color4f {
    float r, g, b, a;
};
static_assert(sizeof(Color4f) == 0x10);

struct Color4u8 {
    u8 r, g, b, a;
};
static_assert(sizeof(Color4u8) == 0x4);

class HandleBase {
public:
    virtual ~HandleBase();

private:
    u64 m_identifier;
    u64 m_unk1;
};
static_assert(sizeof(HandleBase) == 0x18);

template <typename T>
class Handle : public HandleBase {
public:
    virtual ~Handle();

    T* getResource() const { return m_resource; }

private:
    T* m_resource;
};
static_assert(sizeof(Handle<void>) == 0x20);

} // namespace util
