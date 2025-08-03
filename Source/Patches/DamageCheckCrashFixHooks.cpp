#include "Patches/DamageCheckCrashFixHooks.hpp"

#include "Core/Logger.hpp"
#include "SDK/Wld/WldBtl.hpp"

s32 PreCheckDamageCrashFixHook::Callback(wld::btl::unit::BTLUNIT* attacker, wld::btl::unit::BTLUNIT* defender, wld::btl::unit::UNITPARTS* defenderParts, wld::btl::data::WeaponData* weapon, s32 mode) {
    if (!weapon) {
        LOG("[PreCheckDamageCrashFixHook::Callback] Returned early for weapon %s.", weapon->WeaponId);
        return 1;
    }
    return Orig(attacker, defender, defenderParts, weapon, mode);
}

s32 CheckDamageCrashFixHook::Callback(wld::btl::unit::BTLUNIT* attacker, wld::btl::unit::BTLUNIT* defender, wld::btl::unit::UNITPARTS* defenderParts, wld::btl::data::WeaponData* weapon, s32 mode) {
    if (!weapon) {
        LOG("[CheckDamageCrashFixHook::Callback] Returned early for weapon %s.", weapon->WeaponId);
        return 0x13;
    }
    return Orig(attacker, defender, defenderParts, weapon, mode);
}