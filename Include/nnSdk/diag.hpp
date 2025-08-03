#pragma once

#include "Types.hpp"

namespace nn::diag {

struct ModuleInfo {
    char* Path;
    u64 BaseAddress;
    u64 Size;
};

u64 GetRequiredBufferSizeForGetAllModuleInfo();
s32 GetAllModuleInfo(ModuleInfo** out, void* buffer, u64 bufferSize);

} // namespace nn::diag