#pragma once

#include "exlaunch/lib.hpp"

HOOK_DEFINE_TRAMPOLINE(AudienceSetItemHook) {

static s32 Callback(void* audience, u32 idx, char* itemId, s32 max, s32 w4);

};