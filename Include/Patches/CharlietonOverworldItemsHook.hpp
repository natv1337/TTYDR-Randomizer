#pragma once

#include "exlaunch/lib.hpp"

//-------------------------------------------------------------------------------------------------
// Inline function hook for handling ui::hud::SelectWindow logic in relation to Charlieton's items.
//-------------------------------------------------------------------------------------------------
HOOK_DEFINE_INLINE(CharlietonItemsHook) {

static void Callback(exl::hook::InlineCtx* ctx);

};