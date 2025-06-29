#pragma once

#include "../Util.hpp"

namespace util {

class HandleBase {
public:
    virtual ~HandleBase();

private:
    u64 m_identifier;
    u64 m_unk1;
};
ASSERT_SIZE(HandleBase, 0x18);

template <typename T>
class Handle : public HandleBase {
public:
    virtual ~Handle();

    T* getResource() { return m_resource; }

private:
    T* m_resource;
};
ASSERT_SIZE(Handle<void>, 0x20);

} // namespace util
