#include "Mod.hpp"

#include "Util.hpp"
#include "SDK.hpp"

#include "exlaunch/lib.hpp"

Mod::Mod() {
    m_settings.RandomizeFieldItems = true;
    m_settings.RandomizeBlockAndChestItems = true;
    m_settings.RandomizeEnemyItems = true;
}

HOOK_DEFINE_INLINE(BtlUnitEquipItemHk) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeEnemyItems) {
            return;
        }

        ctx->X[22] = reinterpret_cast<u64>(Util::getRandomItemId());
    }
};

HOOK_DEFINE_INLINE(EntryDropForMobjHk1) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeBlockAndChestItems) {
            return;
        }

        ctx->X[0] = reinterpret_cast<u64>(Util::getRandomItemId());
    }
};

HOOK_DEFINE_INLINE(EntryDropForMobjHk2) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeBlockAndChestItems) {
            return;
        }

        ctx->X[0] = reinterpret_cast<u64>(Util::getRandomItemId());
    }
};

HOOK_DEFINE_INLINE(FieldItemHk) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (!g_mod->getSettings().RandomizeFieldItems) {
            return;
        }

        auto fieldItem = reinterpret_cast<wld::fld::data::DisposItem*>(ctx->X[8]);
        if (strstr(fieldItem->ItemIdentifier, "ITEM_KEY_")) {
            return;
        }

        fieldItem->ItemIdentifier = Util::getRandomItemId();
    }
};


void Mod::setupGameHooks() {
    BtlUnitEquipItemHk::InstallAtOffset(static_cast<ptrdiff_t>(0x44b6c0));

    EntryDropForMobjHk1::InstallAtOffset(static_cast<ptrdiff_t>(0x603c34));
    EntryDropForMobjHk2::InstallAtOffset(static_cast<ptrdiff_t>(0x603c40));

    FieldItemHk::InstallAtOffset(static_cast<ptrdiff_t>(0x3ea814));
}