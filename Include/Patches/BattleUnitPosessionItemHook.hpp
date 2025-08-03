#pragma once

#include "exlaunch/lib.hpp"

//------------------------------------------------------------
// Inline function hook for setting an enemy unit's held item.
//------------------------------------------------------------
HOOK_DEFINE_INLINE(BattleUnitPosessionItemHook) {

static void Callback(exl::hook::InlineCtx* ctx);

};