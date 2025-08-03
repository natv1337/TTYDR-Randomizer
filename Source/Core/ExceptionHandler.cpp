#include "Core/ExceptionHandler.hpp"

#include "nnSdk/diag.hpp"
#include "nnSdk/os.hpp"

#include "Core/Logger.hpp"
#include "Core/Mod.hpp"

#include <filesystem>

const char* getFileNameFromPath(char* path) {
    if (!path) {
        return "";
    }

    std::filesystem::path fsPath(path);
    return fsPath.filename().string().c_str();
}

void ExceptionHandler::userExceptionHandler(nn::os::UserExceptionInfo* info) {
#ifdef MOD_DEBUG
    LOG("[UserExceptionHandler] Exception caught (core: %d)", nn::os::GetCurrentCoreNumber());
    LOG("[UserExceptionHandler] Type: %d (%s)", info->ExceptionType, getUserExceptionTypeString(info->ExceptionType));

    for (s32 i = 0; i < 29; i++) {
        LOG("[UserExceptionInfo] X%d = 0x%16llX", i, info->Registers[i]);
    }

    LOG("[UserExceptionHandler] X29 (FP) = 0x%016llX (%21lld)", info->FP.X, info->FP.X);
    LOG("[UserExceptionHandler] X30 (LR) = 0x%016llX (%21lld)", info->LR.X, info->LR.X);
    LOG("[UserExceptionHandler] SP = 0x%016llX (%21lld)", info->SP.X, info->SP.X);
    LOG("[UserExceptionHandler] PC = 0x%016llX (%21lld)", info->PC.X, info->PC.X);

    u64 moduleInfoBufferSize = nn::diag::GetRequiredBufferSizeForGetAllModuleInfo();
    void* moduleInfoBuffer = ALLOCATE(moduleInfoBufferSize);
    nn::diag::ModuleInfo* modules = nullptr;

    s32 moduleCount = nn::diag::GetAllModuleInfo(&modules, moduleInfoBuffer, moduleInfoBufferSize);

    LOG("[UserExceptionHandler] Modules (%d):", moduleCount);
    for (s32 i = 0; i < moduleCount; i++) {
        const nn::diag::ModuleInfo& currentModule = modules[i];
        LOG("0x%016llX (0x%016llX) %s", currentModule.BaseAddress, currentModule.Size, getFileNameFromPath(currentModule.Path));
    }
#endif
}