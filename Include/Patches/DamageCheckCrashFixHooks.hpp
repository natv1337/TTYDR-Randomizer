#pragma once

#include "exlaunch/lib.hpp"

namespace wld::btl {
namespace data {
struct WeaponData;
} // namespace wld::btl::data
namespace unit {
class BTLUNIT;
class UNITPARTS;
} // namespace wld::btl::unit
} // namespace wld::btl

//-------------------------------------------------------------------------  
// PreCheckDamage function hook to handle a null-pointer dereference crash.
//-------------------------------------------------------------------------
HOOK_DEFINE_TRAMPOLINE(PreCheckDamageCrashFixHook) {

static s32 Callback(wld::btl::unit::BTLUNIT* attacker, wld::btl::unit::BTLUNIT* defender, wld::btl::unit::UNITPARTS* defenderParts, wld::btl::data::WeaponData* weapon, s32 mode);

};

//----------------------------------------------------------------------
// CheckDamage function hook to handle a null-pointer dereference crash.
//----------------------------------------------------------------------
HOOK_DEFINE_TRAMPOLINE(CheckDamageCrashFixHook) {

static s32 Callback(wld::btl::unit::BTLUNIT* attacker, wld::btl::unit::BTLUNIT* defender, wld::btl::unit::UNITPARTS* defenderParts, wld::btl::data::WeaponData* weapon, s32 mode);

};