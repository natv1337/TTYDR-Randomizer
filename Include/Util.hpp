#pragma once

#include "Types.hpp"

#include <utility>

namespace Util {

uintptr_t getBaseAddress();
bool isItemAllowedForRandomizer(const char* id);
bool shouldItemBeRandomized(const char* id);
s32 getRandomNumberInRange(s32 lowerBound, s32 upperBound);
char* getRandomItemId();

bool isStringValidIpAddress(const char* input);

template <typename TRet, typename... TArgs>
TRet callFunction(uintptr_t offset, TArgs... args) {
    using tFunc = TRet (*)(TArgs...);
    auto pFunc = reinterpret_cast<tFunc>(getBaseAddress() + offset);
    return pFunc(std::forward<TArgs>(args)...);
}

} // namespace Util

#define GET_STATIC_INSTANCE(t, offset)                                                                                 \
    static t* getInstance() { return *reinterpret_cast<t**>(Util::getBaseAddress() + offset); }

#define ASSERT_SIZE(t, offset) static_assert(sizeof(t) == offset)
