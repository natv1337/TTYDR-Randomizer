#include "Patches/FsManagerCtorHook.hpp"

#include "Core/Mod.hpp"

void FsManagerCtorHook::Callback(fs::Manager* thisp) {
    Orig(thisp);
    g_mod->mountSdCard();
}