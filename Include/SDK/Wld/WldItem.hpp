#pragma once

#include "Types.hpp"
#include "WldHandle.hpp"

namespace wld::fld::item {

enum ItemKind : s32 {
    ItemKind_None = 0x00,
    ItemKind_KeyNormal = 0x01,
    ItemKind_KeyKey = 0x02,
    ItemKind_KeyStage = 0x03,
    ItemKind_KeyStarstone = 0x04,
    ItemKind_UseNormal = 0x05,
    ItemKind_UseAttack = 0x06,
    ItemKind_UseDefence = 0x07,
    ItemKind_UseSupport = 0x08,
    ItemKind_UseRecovery = 0x09,
    ItemKind_UseOther = 0x0A,
    ItemKind_UseCook = 0x0B,
    ItemKind_Trash = 0x0C,
    ItemKind_BadgeJump = 0x0D,
    ItemKind_BadgeHammer = 0x0E,
    ItemKind_BadgeCommand = 0x0F,
    ItemKind_BadgeParam = 0x10,
    ItemKind_BadgeStatus = 0x11,
    ItemKind_BadgeOther = 0x12,
    ItemKind_Immediately = 0x13
};

class Item {
};

typedef wld::Handle<Item> ItemHandle;

} // namespace wld::fld::item