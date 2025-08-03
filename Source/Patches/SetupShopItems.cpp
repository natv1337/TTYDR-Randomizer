#include "Patches/SetupShopItemsHook.hpp"

#include "SDK/String.hpp"
#include "Core/Logger.hpp"
#include "Offsets.hpp"

struct ShopItem {
    String ItemId;
    s32 ItemCost;
    s32 Unk1;
    s32 Unk2;
    s32 Unk3;
};
ASSERT_SIZE(ShopItem, 0x28);

template <typename T>
struct Vector {
    T* Begin;
    T* End;

    size_t length() {
        return ((u64)End - (u64)Begin) / sizeof(T);
    }

    T& operator [](int index) {
        return Begin[index];
    }
};

void SetupShopItemsHook::Callback(exl::hook::InlineCtx* ctx) {
    Vector<ShopItem>* shopItemVec = reinterpret_cast<Vector<ShopItem>*>(Util::getBaseAddress() + Offsets::s_shopDataVector);

    for (size_t i = 0; i < shopItemVec->length(); i++) {
        const char* itemId = shopItemVec->Begin[i].ItemId.getCString();
        if (!Util::shouldItemBeRandomized(itemId)) {
            continue;
        }

        wld::fld::data::ItemData* itemList = Util::getItemDataArray();
        s32 randomIdx = Util::getRandomItemIndex();

        shopItemVec->Begin[i].ItemId.assign(itemList[randomIdx].Identifier);
        shopItemVec->Begin[i].ItemCost = itemList[randomIdx].DefaultPrice;

        LOG("[SetupShopItemsHook::Callback] %s -> %s", itemId, itemList[randomIdx].Identifier);
    }
}