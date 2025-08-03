#include "Util.hpp"

#include <random>

#include "SDK.hpp"
#include "exlaunch/lib.hpp"
#include "nnSdk/socket.hpp"

#include "SDK/Wld/WldFld.hpp"

static constexpr s32 s_randomItemIdMin = 0;
static constexpr s32 s_randomItemIdMax = 341;

uintptr_t Util::getBaseAddress() { 
    return exl::util::modules::GetTargetStart();
}

bool Util::isItemAllowedForRandomizer(wld::fld::data::ItemData* itemData) {
    using namespace wld::fld::item;
    switch (itemData->ItemKind) {
    case ItemKind::ItemKind_None:
    case ItemKind::ItemKind_KeyNormal:
    case ItemKind::ItemKind_KeyKey:
    case ItemKind::ItemKind_KeyStage:
    case ItemKind::ItemKind_KeyStarstone:
    case ItemKind::ItemKind_UseNormal:
    case ItemKind::ItemKind_Trash:
    case ItemKind::ItemKind_Immediately:
        return false;
    case ItemKind::ItemKind_UseOther:
        if (strcmp(itemData->Identifier, "ITEM_USE_TANKOBU_STRONG") == 0) {
            return false;
        }
        return true;
    default:
        return true;
    }

    return true;
}

bool Util::shouldItemBeRandomized(const char* id) {
    return strstr(id, "ITEM_KEY_") == nullptr;
}

s32 Util::getRandomNumberInRange(s32 lowerBound, s32 upperBound) {
    std::mt19937 s_randomEngine{static_cast<std::mt19937::result_type>(svcGetSystemTick())};
    std::uniform_int_distribution<s32> dis(lowerBound, upperBound);

    return dis(s_randomEngine);
}

char* Util::getRandomItemId() {
    wld::fld::data::ItemData* itemList = Util::getItemDataArray();

    s32 randomItemIdx = 0;
    do {
        randomItemIdx = Util::getRandomNumberInRange(s_randomItemIdMin, s_randomItemIdMax);\
    } while (!Util::isItemAllowedForRandomizer(&itemList[randomItemIdx]));

    return itemList[randomItemIdx].Identifier;
}

s32 Util::getRandomItemIndex() {
    wld::fld::data::ItemData* itemList = Util::getItemDataArray();

    u32 itemId = 0;
    do {
        itemId = Util::getRandomNumberInRange(s_randomItemIdMin, s_randomItemIdMax);
    } while (!Util::isItemAllowedForRandomizer(&itemList[itemId]));

    return itemId;
}

bool Util::isItemKindBadge(wld::fld::item::ItemKind kind) {
    return (kind > wld::fld::item::ItemKind_Trash && kind < wld::fld::item::ItemKind_Immediately);
}

s32 Util::getRandomBadgeItemIndex() {
    wld::fld::data::ItemData* itemList = Util::getItemDataArray();

    u32 itemId = 0;
    do {
        itemId = Util::getRandomNumberInRange(s_randomItemIdMin, s_randomItemIdMax);
    } while (!Util::isItemAllowedForRandomizer(&itemList[itemId]) || !isItemKindBadge(itemList[itemId].ItemKind));

    return itemId;
}

wld::fld::data::ItemData* Util::getItemDataArray() {
    return wld::fld::getItemDataArray();
}

bool Util::isIpv4AddressValid(const char* address) {
    sockaddr addr;
    return nn::socket::InetPton(2, address, &addr) == 1;
}
