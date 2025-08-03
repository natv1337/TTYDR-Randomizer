#include "Core/Hooks.hpp"

#include "Offsets.hpp"
#include "Util.hpp"

#include "Patches/MainInitHook.hpp"
#include "Patches/FsManagerCtorHook.hpp"
#include "Patches/BattleUnitPosessionItemHook.hpp"
#include "Patches/SetupShopItemsHook.hpp"
#include "Patches/DamageCheckCrashFixHooks.hpp"
#include "Patches/SetBadgeShopItemsHook.hpp"
#include "Patches/CharlietonOverworldItemsHook.hpp"
#include "Patches/CharlietonPitItemsHook.hpp"
#include "Patches/EntryDropForMobjHook.hpp"
#include "Patches/SetDazzleItemsHook.hpp"
#include "Patches/SetFieldItemHook.hpp"
#include "Patches/AudienceSetItemHook.hpp"

// HOOK_DEFINE_TRAMPOLINE(GswfGetValue) {
//     static s32 Callback(Gswf* gswf, const char* flag) {
//         s32 result = Orig(gswf, flag);
//         if (strstr(flag, "GSWF_BTL_MONOSIRI_UNITKIND")) {
//             return result;
//         }
//         if (strstr(flag, "GSWF_SHINE_") || strstr(flag, "GSWF_STARPIECE_")) {
//             return result;
//         }

//         LOG("[GSWFGetValue] %s (%d)", flag, result);
//         return result;
//     }
// };

// HOOK_DEFINE_TRAMPOLINE(GswfSetValue) {
//     static void Callback(Gswf* gswf, const char* flag, s32 value) {
//         Orig(gswf, flag, value);
//         LOG("[GSWFSetValue] %s (%d)", flag, value);
//     }
// };

// HOOK_DEFINE_TRAMPOLINE(GswGetValue) {
//     static s32 Callback(Gswf* gswf, const char* flag) {
//         s32 result = Orig(gswf, flag);
//         LOG("[GSWGetValue] %s (%d)", flag, result);
//         return result;
//     }
// };

// HOOK_DEFINE_TRAMPOLINE(GswSetValue) {
//     static void Callback(Gswf* gswf, const char* flag, s32 value) {
//         Orig(gswf, flag, value);
//         LOG("[GSWSetValue] %s (%d)", flag, value);
//     }
// };

// HOOK_DEFINE_TRAMPOLINE(LoadMapHk) {
//     static void Callback(void* x0, char* x1, const char* x2) {
//         if (strcmp(x2, "aaa_00")) {
//             return Orig(x0, x1, "gor_00");
//         }
//         if (strcmp(x2, "prologue_from_the_start")) {
//             return Orig(x0, x1, "from_prologue");
//         }
//         return Orig(x0, x1, x2);
//     }
// };

// static const char* g_map = "gor_00";
// HOOK_DEFINE_INLINE(BeginningMapHk) {
//     static void Callback(exl::hook::InlineCtx* ctx) {
//         ctx->X[2] = (u64)g_map;
//     }
// };

void Hooks::installHooks() {
    MainInitHook::InstallAtOffset(Offsets::s_mainInitialization);
    FsManagerCtorHook::InstallAtOffset(Offsets::s_fsManagerCtor);

    SetFieldItemHook::InstallAtOffset(Offsets::s_fieldItemIdHook);
    BattleUnitPosessionItemHook::InstallAtOffset(Offsets::s_battleUnitSetItemHook);
    EntryDropForMobjHook::InstallAtOffset(Offsets::s_itemDropForMobjHook);
    SetupShopItemsHook::InstallAtOffset(Offsets::s_setupShopItemsHook);
    PreCheckDamageCrashFixHook::InstallAtOffset(Offsets::s_damageCheckHook1);
    CheckDamageCrashFixHook::InstallAtOffset(Offsets::s_damageCheckHook2);
    SetBadgeShopItemsHook::InstallAtOffset(Offsets::s_setBadgeShopItemsHook);
    CharlietonItemsHook::InstallAtOffset(Offsets::s_charlietonOverworldItemsHook);
    CharlietonPitItemsHook::InstallAtOffset(Offsets::s_charlietonPitItemsHook);
    DazzleItemsHook::InstallAtOffset(Offsets::s_setDazzleItemsHook);
    AudienceSetItemHook::InstallAtOffset(Offsets::s_audienceSetItemHook);
    // GswfGetValue::InstallAtOffset(0x2b0e58);
    // GswfSetValue::InstallAtOffset(0x2b0f94);
    // GswSetValue::InstallAtOffset(0x2b0c40);
    // GswGetValue::InstallAtOffset(0x2b0b0c);

    // PouchInitializeHk::InstallAtOffset(0x2a7a20);
    // BeginningMapHk::InstallAtOffset(0xa1cdb4);
}
