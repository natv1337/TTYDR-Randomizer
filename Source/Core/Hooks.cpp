#include "Core/Hooks.hpp"

#include "exlaunch/lib.hpp"

#include "Core/Mod.hpp"
#include "SDK.hpp"
#include "Util.hpp"

#include "nnSdk/fs.hpp"

#include "Offsets.hpp"

// Anything that needs to run before game initialization goes here (code after call to Orig will not run).
HOOK_DEFINE_TRAMPOLINE(nnMainHk) {
    static void Callback() {
        Orig();
    }
};

// Important code that should be ran after the game finishes initializing should go here.
HOOK_DEFINE_TRAMPOLINE(MainInitHk) {
    static void Callback() {
        Orig();
    }
};

// Code that requires fs::Manager to be initialized first should go here (only needed for nn::fs::MountSdCardForDebug)
HOOK_DEFINE_TRAMPOLINE(fsManagerCtorHk) {
    static void Callback(void* thisp) {
        Orig(thisp);
        nn::fs::MountSdCardForDebug("sd");
    };
};

// Sets a held item for a battle unit.
HOOK_DEFINE_INLINE(BtlUnitEquipItemHk) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeEnemyItems) {
            return;
        }

        ctx->X[22] = reinterpret_cast<u64>(Util::getRandomItemId());
    }
};

/*
    Enemies using certain items causes a null-pointer exception in certain fuctions. The next two hooks adds a check
    for a null WeaponData pointer and returns early if true.
*/
HOOK_DEFINE_TRAMPOLINE(CheckDamageHk) {
    static s32 Callback(void* attackingUnit, void* defeindingUnit, void* unitParts, void* weaponData, u32 w4) {
        if (!weaponData) {
            return 1;
        }

        return Orig(attackingUnit, defeindingUnit, unitParts, weaponData, w4);
    }
};

HOOK_DEFINE_TRAMPOLINE(CheckDamage2Hk) {
    static s32 Callback(void* attackingUnit, void* defeindingUnit, void* unitParts, void* weaponData, u32 w4) {
        if (!weaponData) {
            return 0x13;
        }

        return Orig(attackingUnit, defeindingUnit, unitParts, weaponData, w4);
    }
};

struct MobjHandle {
    void** vmt;
    u64 unk1;
    u32 unk2;
    u32 unk3;
    void* res;
};

HOOK_DEFINE_TRAMPOLINE(EntryDropForMobjHk) {
    static MobjHandle Callback(void* name, void* identifier, float* pos) {
        if (!g_mod->getSettings().RandomizeBlockAndChestItems) {
            return Orig(name, identifier, pos);
        }

        const char* currentItemId = Util::callFunction<const char*, void*>(
            Offsets::s_stringTypeToCString, name
        );

        if (!Util::shouldItemBeRandomized(currentItemId)) {
            return Orig(name, identifier, pos);
        }
        
        Util::callFunction<void, void*, char*>(
            Offsets::s_copyCStringToStringType, name, Util::getRandomItemId()
        );
        identifier = name;

        return Orig(name, identifier, pos);
    }
};

HOOK_DEFINE_INLINE(FieldItemHk) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeFieldItems) {
            return;
        }

        auto fieldItem = reinterpret_cast<wld::fld::data::DisposItem*>(ctx->X[8]);
        if (!Util::shouldItemBeRandomized(fieldItem->ItemIdentifier)) {
            return;
        }

        fieldItem->ItemIdentifier = Util::getRandomItemId();
    }
};

static const char* g_currentShopItem = "ITEM_NULL";
HOOK_DEFINE_INLINE(ShopItemIdHk) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeShopItems) {
            return;
        }

        if (!Util::shouldItemBeRandomized(reinterpret_cast<const char*>(ctx->X[1]))) {
            return;
        }

        g_currentShopItem = Util::getRandomItemId();
        ctx->X[1] = reinterpret_cast<u64>(g_currentShopItem);
    }
};

HOOK_DEFINE_INLINE(ShopItemPriceHk) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeShopItems) {
            return;
        }

        auto* itemData = Util::callFunction<wld::fld::data::ItemData*, const char*>(
            0x55b650, 
            g_currentShopItem
        );

        ctx->W[8] = itemData->DefaultPrice;
    }
};

void Hooks::installHooks() {
    nnMainHk::InstallAtSymbol("nnMain");
    
    MainInitHk::InstallAtOffset(Offsets::s_mainInitialization);
    fsManagerCtorHk::InstallAtOffset(Offsets::s_fsManagerCtor);
    FieldItemHk::InstallAtOffset(Offsets::s_fieldItemIdHook);
    BtlUnitEquipItemHk::InstallAtOffset(Offsets::s_battleUnitSetItemHook);
    EntryDropForMobjHk::InstallAtOffset(Offsets::s_itemDropForMobjHook);
    ShopItemIdHk::InstallAtOffset(Offsets::s_shopItemIdHook);
    ShopItemPriceHk::InstallAtOffset(Offsets::s_shopItemPriceHook);
    CheckDamageHk::InstallAtOffset(Offsets::s_damageCheckHook1);
    CheckDamage2Hk::InstallAtOffset(Offsets::s_damageCheckHook2);
}
