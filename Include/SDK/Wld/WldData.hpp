#pragma once

#include "../../Util.hpp"

#include "WldItem.hpp"

namespace wld::fld::data {

struct ItemData {
    char* Identifier;                  // 0x00
    char* JpIdentifier;                // 0x08
    wld::fld::item::ItemKind ItemKind; // 0x10
    char* ItemName;                    // 0x18
    char* IconId;                      // 0x20
    char* LabelId;                     // 0x28
    char* ContentsLabelId;             // 0x30
    char* MonosiriLabelId;             // 0x38
    s16 SortOrder;                     // 0x40
    s16 DefaultPrice;                  // 0x42
    s16 DiscountPrice;                 // 0x44
    s16 StarPiecePrice;                // 0x46
    s16 SellValue;                     // 0x48
    bool UsableInField;                // 0x4A
    bool UsableInBattle;               // 0x4B
    bool UsableInShop;                 // 0x4C
    s8 BpCost;                         // 0x4D
    s8 HpRestored;                     // 0x4E
    s8 FpRestored;                     // 0x4F
private:
    s32 int_0050;
    s32 int_0054;
public:
    char* WeaponName;                  // 0x58
    char* SfxPickupName;               // 0x60
    char* EffUseName;                  // 0x68
    char* EffPickupName;               // 0x70
private:
    u64 long_0078;
public:
    char* SfxBounceName;               // 0x80
private:
    u64 long_0088;
    u64 long_0090;
    u32 int_0098;
    u32 int_009C;
};
static_assert(sizeof(ItemData) == 0xA0);

struct UIModelPropertyData {
    char pad_0000[0x40];
};
static_assert(sizeof(UIModelPropertyData) == 0x40);

struct UIModelData {
    char* Identifier;
    char* Directory;

    // wld::fld::data::s_uiModelPropertyData_ + PropertyIdentifier
    char* PropertyIdentifier; 

    UIModelPropertyData* Properties;
    s32 PropertyCount;
};
static_assert(sizeof(UIModelData) == 0x28);

struct UIMessageData {
    char* Identifier;
    char* UiDirectory;
    char* WindowInName;
    char* WindowOutName;

};

struct UIMailData {
    char* Identifier;
    u32 Flags;
    char* TitleMessageId;
    char* SenderMessageId;
    char* ContentsMessageId;
    char* AltContentsMessageId;
    s32 Int0030;
    u32 Uint0034;
};
static_assert(sizeof(UIMailData) == 0x38);

struct UIStarpieceData {
    // GSWF flag for star piece
    char* GswfIdentifier;

    char* JpIdentifier;

    // Map star piece is found in
    char* MapIdentifier;

    // Earliest sequence to show
    char* AssociatedSequence;

    // MSBT message identifier
    char* MessageId;
};
static_assert(sizeof(UIStarpieceData) == 0x28);

}