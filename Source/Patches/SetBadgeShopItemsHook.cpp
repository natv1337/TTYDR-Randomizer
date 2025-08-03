#include "Patches/SetBadgeShopItemsHook.hpp"

#include "SDK/Pouch.hpp"

void SetBadgeShopItemsHook::Callback(exl::hook::InlineCtx* ctx) {
    for (auto& it : pouch::Pouch::getInstance()->ShopInfo.SoldBadges) {
        it = Util::getRandomBadgeItemIndex();
    }
}