/**
 * @file Hid.hpp
 * @brief Class definitions for the hid namespace.
 */
#pragma once

#include "Util.hpp"
#include "Offsets.hpp"

namespace hid {

class BasePad {
public:
    virtual void zeroPadState() = 0;
};
ASSERT_SIZE(BasePad, 0x08);

class DebugPad : public BasePad {
public:
    virtual void zeroPadState() override;

private:
    char pad_0008[0x1A8];
};
ASSERT_SIZE(DebugPad, 0x1B0);

class JoyPad : public BasePad {
public:
    virtual void zeroPadState() override;

private:
    char pad_0008[0x128];
};
ASSERT_SIZE(JoyPad, 0x130);

class DebugInput {

};

class Manager {
public:
    GET_STATIC_INSTANCE(Manager, Offsets::s_hidManager)

private:
    DebugPad m_debugPad;
    JoyPad m_joyPad;
    char pad_02E0[0x1C0];

};
ASSERT_SIZE(Manager, 0x4A0);

} // namespace hid
