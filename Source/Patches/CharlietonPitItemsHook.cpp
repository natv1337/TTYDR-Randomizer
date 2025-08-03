#include "Patches/CharlietonPitItemsHook.hpp"

#include "SDK/Gswf.hpp"
#include "SDK/Wld/WldFld.hpp"

void CharlietonPitItemsHook::Callback(exl::hook::InlineCtx* ctx) {
    u16* itemIdx = reinterpret_cast<u16*>(ctx->X[10] + 0x2E);
    if (*itemIdx == 0) {
        return;
    }
    u16* price = reinterpret_cast<u16*>(ctx->X[10] + 0x30);
    if (*price == 0) {
        return;
    }


    s32 floor = Gswf::getInstance()->getGsTableValue("GSW_JON_FLOOR");
    float priceParam = wld::fld::getFloatParameter("JON_SHOP_PRICE_PARAM");
    float maxPriceParam = wld::fld::getFloatParameter("JON_SHOP_PRICE_MAX");
    wld::fld::data::ItemData* itemArray = wld::fld::getItemDataArray();

    u16 newItemIdx = static_cast<u16>(Util::getRandomItemIndex());
    u16 newPrice = (floor + static_cast<s32>(priceParam)) * itemArray[newItemIdx].DefaultPrice / 10;
    newPrice = (newPrice > static_cast<u16>(maxPriceParam)) ? static_cast<u16>(maxPriceParam) : newPrice;

    *itemIdx = newItemIdx;
    *price = newPrice;
}