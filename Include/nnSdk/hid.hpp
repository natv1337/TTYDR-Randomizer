#pragma once

#include "Types.hpp"
#include "util_BitFlagSet.hpp"

namespace nn::hid {

enum class NpadAttribute {
    IsConnected = 0,
    IsWired = 1,
    IsLeftConnected = 2,
    IsLeftWired = 3,
    IsRightConnected = 4,
    IsRightWired = 5,
};

enum class NpadButton {
    A = 0,
    B = 1,
    X = 2,
    Y = 3,
    StickL = 4,
    StickR = 5,
    L = 6,
    R = 7,
    ZL = 8,
    ZR = 9,
    Plus = 10,
    Minus = 11,
    Left = 12,
    Up = 13,
    Right = 14,
    Down = 15,
    StickLLeft = 16,
    StickLUp = 17,
    StickLRight = 18,
    StickLDown = 19,
    StickRLeft = 20,
    StickRUp = 21,
    StickRRight = 22,
    StickRDown = 23,
    LeftSL = 24,
    LeftSR = 25,
    RightSL = 26,
    RightSR = 27,
    Palma = 28,
    Verification = 29,
    HandheldLeftB = 30,  // (Left B button on NES controllers in Handheld mode)
    LeftC = 31,          // [12.0.0+] (Left C button in N64 controller)
    UpC = 32,            // [12.0.0+] (Up C button in N64 controller)
    RightC = 33,         // [12.0.0+] (Right C button in N64 controller)
    DownC = 34,          // [12.0.0+] (Down C button in N64 controller)
};

typedef nn::util::BitFlagSet<32, NpadAttribute> NpadAttributeSet;
typedef nn::util::BitFlagSet<64, NpadButton> NpadButtonSet;

struct AnalogStickState {
    s32 X, Y;
};

struct NpadBaseState {
    u64 SamplingNumber;
    NpadButtonSet Buttons;
    AnalogStickState AnalogStickL;
    AnalogStickState AnalogStickR;
    NpadAttributeSet Attributes;
};

} // nn::hid