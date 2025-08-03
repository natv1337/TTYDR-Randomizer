#pragma once

#include "WldChr.hpp"
#include "../Math.hpp"
#include "../String.hpp"

#include "../../Util.hpp"

namespace wld::btl {

namespace data {

struct WeaponData {
    char* WeaponId;
    char* MsgNameId;
    char* IconId;
    char* ItemName;
    char* MsgDescId;
    s32 BaseAccuracy;
    s32 FpCost;
    s32 SpCost;
    float ActionCommandBaseValue;
};

} // namespace wld::btl::data

namespace item {

class Manager : public wld::chr::Manager {
public:
    virtual ~Manager() override;
    virtual void Deleter() override;
    virtual void Vfunc3() override;
    virtual void Vfunc4() override;

private:

};

} // namespace wlditem

namespace unit {

enum BtlBelong : s32 {
    BtlBelong_PLAYER = 0x00,
    BtlBelong_MONSTER = 0x01,
    BtlBelong_NEUTRAL = 0x02
};

enum Status {
    Status_Allergy = 0x00,
    Status_Sleep = 0x01,
    Status_Stop = 0x02,
    Status_Dizzy = 0x03,
    Status_Poison = 0x04,
    Status_Confusion = 0x05,
    Status_Electric = 0x06,
    Status_Dodge = 0x07,
    Status_Burn = 0x08,
    Status_Freeze = 0x09,
    Status_Big = 0x0A,
    Status_Small = 0x0B,
    Status_AttackUp = 0x0C,
    Status_AttackDown = 0x0D,
    Status_Hard = 0x0E,
    Status_Soft = 0x0F,
    Status_Charge = 0x10,
    Status_Flipped = 0x11,
    Status_Invisible = 0x12,
    Status_Quick = 0x13,
    Status_Slow = 0x14,
    Status_Payback = 0x15,
    Status_HoldFast = 0x16,
    Status_HpRegen = 0x17,
    Status_FpRegen = 0x18,
    Status_Fright = 0x19,
    Status_GaleForce = 0x1A,
    Status_InstantKill = 0x1B,
    Status_NoJump = 0x1C,
    Status_NoHammer = 0x1D,
    Status_MajinaiPowerup = 0x1E,
    Status_MajinaiDefenseUp = 0x1F,
    Status_Normal = 0x20
};

enum SwallowAttribute : s32 {
    SwallowAttribute_None = 0,
    SwallowAttribute_Involved = 1 << 0,
    SwallowAttribute_Explosion = 1 << 1,
    SwallowAttribute_Fuel = 1 << 2,
    SwallowAttribute_SamboBody = 1 << 3
};

enum UnitAttr {
    UnitAttr_Null = 0,
    UnitAttr_MapObj = 1 << 0,
    UnitAttr_Ceil = 1 << 1,
    UnitAttr_Fly = 1 << 2,
    UnitAttr_Trans = 1 << 3,
    UnitAttr_Hide = 1 << 4,
    UnitAttr_KouraGuard = 1 << 5,
    UnitAttr_KouraGuardEnable = 1 << 6,
    UnitAttr_LimitSwitch = 1 << 7,
    UnitAttr_DodgeJump = 1 << 8,
    UnitAttr_DodgeHammer = 1 << 9,
    UnitAttr_DodgeAll = 1 << 10,
    UnitAttr_NoStatusEffect = 1 << 11,
    UnitAttr_DontBlow = 1 << 12,
    UnitAttr_Undead = 1 << 13,
    UnitAttr_Corpse = 1 << 14,
    UnitAttr_Leader = 1 << 15,
    UnitAttr_RealTime = 1 << 16,
    UnitAttr_HpFpTransDisable = 1 << 17,
    UnitAttr_NoSpin = 1 << 18,
    UnitAttr_NoDispDamage = 1 << 19,
    UnitAttr_DispOff = 1 << 20,
    UnitAttr_HPGaugeOff = 1 << 21,
    UnitAttr_LookCamera = 1 << 22,
    UnitAttr_Noncombatant = 1 << 23,
    UnitAttr_NoShadow = 1 << 24,
    UnitAttr_HPInfinity = 1 << 25
};

enum UnitKind : s32 {
    UnitKind_Null = 0,
    UnitKind_Enemy = 1,
    UnitKind_MapObj = 2,
    UnitKind_Npc = 3,
    UnitKind_Mario = 4,
    UnitKind_MarioEtc = 5,
    UnitKind_Party = 6
};

enum UnitFlag : s32 {
    UnitFlag_HpDamageGaugeDisp = 1 << 0,
    UnitFlag_ColorLvChange = 1 << 1,
    UnitFlag_UnitKindChange = 1 << 2,
    UnitFlag_NoPartyCharactor = 1 << 3,
    UnitFlag_BattleEscapeDisable = 1 << 4,
    UnitFlag_Drain_Pose = 1 << 8,
    UnitFlag_HideShadow = 1 << 16,
    UnitFlag_DekaBounding = 1 << 17,
    UnitFlag_Float = 1 << 20,
    UnitFlag_FloatControl = 1 << 21,
    UnitFlag_LONG_DAMAGE_MOTION = 1 << 22,
    UnitFlag_PreDead = 1 << 23,
    UnitFlag_PaperCraft = 1 << 24,
    UnitFlag_ItemForceDisp = 1 << 25,
    UnitFlag_Act_ItemNoDisp = 1 << 26,
    UnitFlag_Dead_ItemNoDisp = 1 << 27,
    UnitFlag_DAMAGE_CANCEL_GUARD = 1 << 28,
    UnitFlag_NoOutFieldBySAC = 1 << 29,
    UnitFlag_ItemStolen = 1 << 30,
    UnitFlag_Broken = 1 << 31
};

struct UnitStatus {
    s32 SleepTurns;       // 0x00
    s32 SleepPower;       // 0x04
    s32 StopTurns;        // 0x08
    s32 DizzyTurns;       // 0x0C
    s32 PoisonTurns;      // 0x10
    s32 PoisonPower;      // 0x14
    s32 ConfuseTurns;     // 0x18
    s32 ElectricTurns;    // 0x1C
    s32 DodgyTurns;       // 0x20
    s32 BurnTurns;        // 0x24
    s32 FreezeTurns;      // 0x28
    s32 BigTurns;         // 0x2C
    s32 SmallTurns;       // 0x30
    s32 AttackUpTurns;    // 0x34
    s32 AttackUpPower;    // 0x38
    s32 SoftTurns;        // 0x3C
    s32 HardTurns;        // 0x40
    s32 ChargePower;      // 0x44
    s32 AllergicTurns;    // 0x48
    s32 FlippedTurns;     // 0x4C
    s32 InvisibleTurns;   // 0x50
    s32 CounterTurns;     // 0x54
    s32 HoldFastTurns;    // 0x58
    s32 QuickTurns;       // 0x5C
    s32 SlowTurns;        // 0x60
    s32 HpRegenTurns;     // 0x64
    s32 HpRegenPower;     // 0x68
    s32 FpRegenTurns;     // 0x6C
    s32 FpRegenPower;     // 0x70
    s32 InstantKillTurns; // 0x74
};
ASSERT_SIZE(UnitStatus, 0x78);

class BTLUNIT {
public:
    virtual ~BTLUNIT();

    void setAttribute(UnitAttr attr) {
        m_attributes = static_cast<UnitAttr>(m_attributes | attr);
    }

    String* getPosessionItem() {
        return &m_posessionItem;
    }

private:
    char pad_0008[0x08];
    s32 m_unitArrayIndex;
    String m_unitKindBase;
    UnitKind m_unkUnitKind;
    String m_tattleLogUnitId;
    String m_unitId;
    UnitKind m_unitKind;
    BtlBelong m_unitBelong;
    s32 m_level;
    s32 m_partyNumber;
    void* ptr_0078;
    void* m_unitData;
    class UNITPARTS* m_unitParts;
    char pad_0090[0x200];
    UnitFlag m_unitFlags;
    s32 int_0294;
    s32 m_maxMoveCount;
    s32 m_moveCount;
    s32 m_currentTurnMaxMoveCount;
    char pad_02A4[0x04];
    s32 m_swallowParam;
    SwallowAttribute m_swallowAttribute;
    char pad_02B0[0x10];
    math::Vec3 m_homePositon;
    math::Vec3 m_position;
    math::Vec3 vec3_02E0;
    math::Vec3 m_displayOffset;
    math::Vec3 m_baseRotate;
    math::Vec3 m_rotate;
    math::Vec3 m_rotateOffset;
    math::Vec3 m_rotateOffsetCenter;
    math::Vec3 m_scale;
    math::Vec3 m_baseScale;
    math::Vec3 m_messageOffset;
    math::Vec3 m_togeOffset;
    math::Vec3 m_positionItemBaseOffset;
    math::Vec3 m_positionItemOffset;
    math::Vec3 m_statusEffectOffset;
    math::Vec3 m_sleepEffectOffset;
    math::Vec3 m_freezeEffectOffset;
    math::Vec3 m_freezeEffectScale;
    math::Vec3 m_electrifiedEffectOffset;
    math::Vec3 m_confusedEffectOffset;
    s32 m_width;
    s32 m_height;
    math::Vec2 m_statusIconOffset;
    math::Vec2 m_hpGaugeOffset;
    char pad_0418[8];
    math::Vec3 m_cutBaseOffset;
    float m_cutWidth;
    float m_cutHeight;
    char pad_0438[8];
    math::Vec3 m_bintaHitOffset;
    math::Vec3 m_kissHitOffset;
    UnitAttr m_attributes;
    s32 m_maxHp;
    s32 m_maxHpBase;
    s32 m_currentHp;
    s32 m_maxFp;
    s32 m_maxFpBase;
    s32 int_0478;
    s32 m_currentFp;
    char pad_0480[0x1210];
    String m_posessionItem;
};
ASSERT_SIZE(BTLUNIT, 0x16A8);

class UNITPARTS {

};

}

} // namespace wld::btl