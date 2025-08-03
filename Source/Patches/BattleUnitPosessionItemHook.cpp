#include "Patches/BattleUnitPosessionItemHook.hpp"

#include "Util.hpp"

#include "SDK/Wld.hpp"
#include "Core/Logger.hpp"

void BattleUnitPosessionItemHook::Callback(exl::hook::InlineCtx* ctx) {
    String* enemyItemId = reinterpret_cast<String*>(ctx->X[0]);
    wld::fld::data::ItemData* itemArray = wld::fld::getItemDataArray();

    s32 itemIdx;
    do {
        itemIdx = Util::getRandomItemIndex();
    } while (!Util::isItemAllowedForRandomizer(&itemArray[itemIdx]));

    enemyItemId->assign(itemArray[itemIdx].Identifier);

    LOG("[BattleUnitPosessionItemHook] %s", itemArray[itemIdx].Identifier);
}