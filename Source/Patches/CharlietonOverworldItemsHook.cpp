#include "Patches/CharlietonOverworldItemsHook.hpp"

#include "Util.hpp"
#include "SDK/Wld/WldFld.hpp"

struct SelectableItem {
    s16 Unk1;
    s16 ItemIdx;
    s16 ItemPrice;
    s16 Unk2;
};

struct SelectionInfo {
    s32 Unk1;
    s32 Unk2;
    s32 Unk3;
    s32 Unk4;
    s32 Unk5;
    SelectableItem Items[4];
};

void CharlietonItemsHook::Callback(exl::hook::InlineCtx* ctx) {
    SelectionInfo* info = reinterpret_cast<SelectionInfo*>(ctx->X[10]);
    wld::fld::data::ItemData* itemList = wld::fld::getItemDataArray();

    float charlietonIncrease = wld::fld::getFloatParameter("GOR_SHOP_PRICE_PARAM");

    for (s32 i = 0; i < 4; i++) {
        s32 idx = Util::getRandomItemIndex();
        info->Items[i].ItemIdx = idx;
        info->Items[i].ItemPrice = static_cast<s32>(charlietonIncrease) * itemList[idx].DefaultPrice / 10;
    }
}