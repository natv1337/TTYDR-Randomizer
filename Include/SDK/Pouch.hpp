/**
 * @file Pouch.hpp
 * @brief Class definitions for the pouch namespace.
 */
#pragma once

#include "../Util.hpp"
#include "String.hpp"

enum Party : s32 {
    Party_None = 0,
    Party_Goombella = 1,
    Party_Koops = 2,
    Party_Bobbery = 3,
    Party_Yoshi = 4,
    Party_Flurrie = 5,
    Party_Vivian = 6,
    Patry_Mowz = 7,
    Party_Max = 8
};

enum ExParty {
    ExParty_None = 8,
    ExParty_Egg = 9,
    ExParty_Marco = 10,
    ExParty_Guide = 11,
    ExParty_Frankly = 12,
    ExParty_Touzokudan_Kobun = 13,
    ExParty_Goombella = 14,
    ExParty_Koops = 15,
    ExParty_Bobbery = 16,
    ExParty_Yoshi = 17,
    ExParty_Flurrie = 18,
    ExParty_Vivian = 19,
    ExParty_Mowz = 20,
    ExParty_Max = 21
};

namespace pouch {

enum PlayerSide : s8 {
    PlayerSide_Mario  = 0,
    PlayerSide_Peach  = 1,
    PlayerSide_Bowser = 2
};

enum EntryMode : s8 {
    EntryMode_None  = 0,
    EntryMode_Slit  = 1,
    EntryMode_Roll  = 2,
    EntryMode_Boat  = 3,
    EntryMode_Yoshi = 4
};

struct Party {
    bool IsJoined;
    bool IsAway; // Used for when a party member temporarliy leaves (such as during Chapter 4)
    s16 Color;
    s16 MaxHp;
    s16 MaxHpBase;
    s16 Hp;
    s16 Level;
};
ASSERT_SIZE(Party, 0x0C);

struct Follower {
    Party PartyId;
    ExParty ExPartyId;
    s32 FollowerId;
};

struct Koopa {
    s32 Coins;
    s32 Score;
};

struct Struct4860 {
    PlayerSide CurrentSide;
    PlayerSide RequestedSide;
    EntryMode PlayerEntry;
    bool IsShadowMario;
};

struct Struct5040 {
    char pad_0000[0x280];
    s32 SoldBadges[5];
    char pad_0294[0x200];
};
ASSERT_SIZE(Struct5040, 0x494);

struct Pouch {
    char SwEventStr[0x10]; // 0x0000
    bool Initialized;      // 0x0010
private:
    char pad_0011[0x07]; // 0x0011
public:
    s16 Hp;           // 0x0018
    s16 MaxHp;        // 0x001A
    s16 Fp;           // 0x001C
    s16 MaxFp;        // 0x001E
    s16 Coins;        // 0x0020
    s16 StarPower;    // 0x0022
    s16 MaxStarPower; // 0x0024
    s16 StarRank;     // 0x0026
private:
    char pad_0028[0x04]; // 0x0028
public:
    float AudienceNum;         // 0x002C
    s16 BattleStage;           // 0x0030
    s16 Level;                 // 0x0032
    s16 AvailableSpecialMoves; // 0x0034
    s16 MaxHpBase;             // 0x0036
    s16 MaxFpBase;             // 0x0038
    s16 Bp;                    // 0x003A
    s16 MaxBp;                 // 0x003C
    s16 StarPoint;             // 0x003E
    s8 JumpLevel;              // 0x0040
    s8 HammerLevel;            // 0x0041
    s16 StarPieces;            // 0x0042
    s16 ShineSprites;          // 0x0044
    s16 PowerbounceRecord;     // 0x0046
    s16 EscapeRate;            // 0x0048
private:
    char pad_004a[0x06]; // 0x004A

public:
    String KeyItems[128]; // 0x0050
    String CurrentItems[20]; // 0x0C50
    String StoredItems[32]; // 0x0E30
    String Badges[200]; // 0x1130
    String EquippedBadges[200]; // 0x23F0
    bool NewBadges[200]; // 0x36B0
    String Mail[99]; // 0x3778
    bool MailOpened[99]; // 0x40C0
    bool MailLook[99]; // 0x4123
    bool GalleryArtOpen[500]; // 0x4186
    bool GallerySoundOpen[500]; // 0x437A
    bool GallerySoundNostalgicOpen[500]; // 0x456E
    s16 ShopPoints; // 0x4762
    s32 ShopPointFlag; // 0x4764
    s8 MerleeCount; // 0x4768
    s8 MerleeTurnCount; // 0x4769
    s8 MerleeEffectType; // 0x476A
    char YoshiName[25]; // 0x476B
    Party PartyData[8]; // 0x4788
    Follower FollowerData; // 0x47E8
    Koopa BowserData; // 0x47F4
    String StageName; // 0x4800
    String CourseName;  // 0x4818
    String MapName; // 0x4830
    String BeroName; // 0x4848
    char pad_4860[0x7E0];
    Struct5040 ShopInfo;

    GET_STATIC_INSTANCE(Pouch, 0x2525040)
};
ASSERT_SIZE(Pouch, 0x54D8);

} // namespace pouch