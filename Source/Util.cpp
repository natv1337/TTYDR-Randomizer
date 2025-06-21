#include "Util.hpp"

#include <random>

#include "exlaunch/lib.hpp"
#include "SDK.hpp"

uintptr_t Util::getBaseAddress() {
    return exl::util::modules::GetTargetStart();
}

bool Util::isItemAllowedForRandomizer(const char* id) {
    if (strcmp(id, "ITEM_NULL") == 0) {
        return false;
    }

    if (strstr(id, "ITEM_KEY_")) {
        return false;
    }

    if (strstr(id, "ITEM_TRASH_")) {
        return false;
    }

    if (strstr(id, "ITEM_USE_COIN")) {
        return false;
    }

    if (strstr(id, "ITEM_USE_MONTE")) {
        return false;
    }

    if (strcmp(id, "ITEM_USE_HEART") == 0) {
        return false;
    }

    if (strcmp(id, "ITEM_USE_FLOWER") == 0) {
        return false;
    }

    if (strstr(id, "ITEM_IMM")) {
        return false;
    }

    return true;
}

s32 Util::getRandomNumberInRange(s32 lowerBound, s32 upperBound) {
    std::mt19937 randomEngine { static_cast<std::mt19937::result_type>(svcGetSystemTick()) };
    std::uniform_int_distribution<s32> dis(lowerBound, upperBound);

    return dis(randomEngine);
}

char* Util::getRandomItemId() {
    fs::ElfFile* characterItemElf = wld::Manager::getInstance()->getCharacterItem()->getElfFile();
    auto itemList = characterItemElf->getElfData().findSymbol<wld::fld::data::ItemData>("wld::fld::data::s_Data");

    char* randomItemStr = nullptr;
    do {
        randomItemStr = itemList[Util::getRandomNumberInRange(0, 341)].Identifier;
    } while (!Util::isItemAllowedForRandomizer(randomItemStr)); 
    
    return randomItemStr;
}