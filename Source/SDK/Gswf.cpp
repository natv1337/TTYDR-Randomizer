#include "SDK/Gswf.hpp"

s32 Gswf::getGsTableValue(const char* key) {
    return Util::callFunction<s32, const char*>(0x2b0b0c, key);
}