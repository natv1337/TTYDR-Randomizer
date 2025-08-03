#include "Patches/SetDazzleItemsHook.hpp"

#include "Util.hpp"
#include "SDK/Wld/WldFld.hpp"
#include "Core/Logger.hpp"

void DazzleItemsHook::Callback(exl::hook::InlineCtx* ctx) {
    u16* itemIdx = reinterpret_cast<u16*>(ctx->X[8] + 0x2E);
    
    // end of list
    if (*itemIdx == 0) {
        return;
    }
    
    u16 newItemId = static_cast<u16>(Util::getRandomItemIndex());
#ifdef MOD_DEBUG
    wld::fld::data::ItemData* itemArray = wld::fld::getItemDataArray();
    LOG("[DazzleItemsHook::Callback] %s -> %s", itemArray[*itemIdx].Identifier, itemArray[newItemId].Identifier);
#endif
    *itemIdx = newItemId;
}