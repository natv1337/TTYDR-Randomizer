#pragma once

#include "Types.hpp"

#include "result.hpp"

namespace nn::time {

enum DayOfTheWeek {
    Sunday,
    Monday,
    Teusday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

struct CalendarTime {
    s16 Year;
    s8 Month;
    s8 Day;
    s8 Hour;
    s8 Minute;
    s8 Second;
};

struct TimeZone {
    char StandardTimeName[0x08];
    bool IsDaylightSavingsTime;
    s32 UtcOffset;
};

struct CalendarAdditionalInfo {
    nn::time::DayOfTheWeek DayOfTheWeek;
    s32 DayOfYear;
    nn::time::TimeZone TimeZone; 
};

struct PosixTime {
    u64 Time;
};

class StandardUserSystemClock {
public:
    static Result GetCurrentTime(nn::time::PosixTime* outTime);
};

Result ToCalendarTime(CalendarTime* outCalendarTime, CalendarAdditionalInfo* outAdditionalInfo, const PosixTime& inPosixTime);

}