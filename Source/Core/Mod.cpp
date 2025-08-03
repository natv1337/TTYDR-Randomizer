#include "Core/Mod.hpp"

#include "Core/Hooks.hpp"
#include "Util.hpp"
#include "Offsets.hpp"

#include "nnSdk/fs.hpp"
#include "nnSdk/os.hpp"
#include "Core/ExceptionHandler.hpp"
#include "Core/Logger.hpp"

Mod::Mod() {
    m_logger = new Logger(LOG_FILE_OUTPUT);

    m_settings = {
        .ModName = MOD_NAME,
        .RandomizeFieldItems = false,
        .RandomizeBlockAndChestItems = false,
        .RandomizeEnemyItems = false,
        .RandomizeShopItems = false
    };
}

Mod::~Mod() {
    delete m_logger;
}

void Mod::initialize() {
    Hooks::installHooks();

#ifdef MOD_DEBUG
    nn::os::SetUserExceptionHandler(ExceptionHandler::userExceptionHandler, nullptr, 0, nullptr);
#endif
}

void* Mod::allocate(size_t size, s32 alignment) {
    return Util::callFunction<void*, void*, size_t, s32, s32>(Offsets::s_ingameAllocate, 
        *reinterpret_cast<void**>(Util::getBaseAddress() + Offsets::s_globalAllocator), 
        size, 
        alignment, 
        0
    );
}

void Mod::deallocate(void* ptr) {
    return Util::callFunction<void, void*>(Offsets::s_ingameFree, ptr);
}

void Mod::mountSdCard() {
#ifdef MOD_DEBUG
    Result rc = nn::fs::MountSdCardForDebug("sd");
    m_isSdCardMounted = rc == 0;
#else
    m_isSdCardMounted = false;
#endif
}