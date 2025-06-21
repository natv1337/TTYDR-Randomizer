#pragma once

#include "Types.hpp"

namespace Util {

uintptr_t getBaseAddress();
bool isItemAllowedForRandomizer(const char* id);
s32 getRandomNumberInRange(s32 lowerBound, s32 upperBound);
char* getRandomItemId();

}