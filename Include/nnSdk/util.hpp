#pragma once

#include <stdarg.h>
#include "Types.hpp"

namespace nn::util {

enum CharacterEncodingResult {
    Success,
    BadLength,
    InvalidFormat
};

s32 SNPrintf(char* s, u64 n, const char* format, ...);
s32 VSNPrintf(char* s, u64 n, const char* format, va_list arg);


CharacterEncodingResult ConvertStringUtf8ToUtf16Native(char16_t* out, s32 len, const char* src, s32 srcLen);
CharacterEncodingResult ConvertStringUtf16NativeToUtf8(char* out, s32 len, const char16_t* src, s32 srcLen);


} // nn::util