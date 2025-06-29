#include "Core/Mod.hpp"

#include "Core/Hooks.hpp"
#include "Util.hpp"
#include "Offsets.hpp"

Mod::Mod() {
    m_settings.ModName = MOD_NAME;
    m_settings.RandomizeFieldItems = true;
    m_settings.RandomizeBlockAndChestItems = true;
    m_settings.RandomizeEnemyItems = true;
    m_settings.RandomizeShopItems = true;
}

void Mod::initialize() {
    Hooks::installHooks();
}

void* Mod::allocate(size_t size) {
    return Util::callFunction<void*, size_t>(Offsets::s_ingameAllocate, size);
}

void Mod::deallocate(void* ptr) {
    return Util::callFunction<void, void*>(Offsets::s_ingameFree, ptr);
}