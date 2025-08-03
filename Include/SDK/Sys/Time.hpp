#pragma once

#include "Types.hpp"
#include "../../Util.hpp"

namespace sys::time {

struct TimeInfo {
private:
    char pad_0000[0x0C]; // 0x00
public:
    float TimeStepScale; // 0x0C
    float FrameCount; // 0x10
private:
    char pad_0014[0x24];
};
ASSERT_SIZE(TimeInfo, 0x38);

class Manager {
public:
    virtual ~Manager();

private:
    u64 m_tickDifference;      // 0x008
    u64 m_previousTick;        // 0x010
    u64 m_unk0018;             // 0x018
    TimeInfo m_timeInfo1;      // 0x020
    TimeInfo m_baseTimeInfo;   // 0x058
    TimeInfo m_fieldTimeInfo;  // 0x090
    TimeInfo m_battleTimeInfo; // 0x0C8
    TimeInfo m_timeInfo5;      // 0x100
    char pad_0138[0x08];       // 0x138

};
ASSERT_SIZE(Manager, 0x140);

} // namespace sys::time