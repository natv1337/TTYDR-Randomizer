#include "Patches/AudienceSetItemHook.hpp"

#include "Util.hpp"

s32 AudienceSetItemHook::Callback(void* audience, u32 idx, char* itemId, s32 max, s32 w4) {
    if (strcmp(itemId, "ITEM_NULL") == 0) {
        return Orig(audience, idx, itemId, max, w4);
    }

    itemId = Util::getRandomItemId();
    return Orig(audience, idx, itemId, max, w4);
}