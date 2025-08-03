/**
 * @file UI.hpp
 * @brief Class definitions for the ui namespace.
 */
#pragma once

#include "../Util.hpp"

namespace ui {

namespace hud {

class Balloon {
public:
    virtual ~Balloon();

private:
    char pad_0008[0x948];

};
ASSERT_SIZE(Balloon, 0x950);

class Caption {
public:
    virtual ~Caption();

private:
    char pad_0008[0x238];
};
ASSERT_SIZE(Caption, 0x240);

class Explain {
public:
    virtual ~Explain();

private:
    char pad_0008[0x248];

};
ASSERT_SIZE(Explain, 0x250);

class Incoming {
public:
    virtual ~Incoming();

private:
    char pad_0008[0x1F8];
};
ASSERT_SIZE(Incoming, 0x200);

class KpaUI {
public:
    virtual ~KpaUI();

private:
    char pad_0008[0x338];
};
ASSERT_SIZE(KpaUI, 0x340);

class PartySelect {
public:
    virtual ~PartySelect();

private:
    char pad_0008[0x378];
};
ASSERT_SIZE(PartySelect, 0x380);

class PuniCounter {
public:
    virtual ~PuniCounter();

private:
    char pad_0008[0x1D8]; // 0x008

};
ASSERT_SIZE(PuniCounter, 0x1E0);

class Telop {
public:
    virtual ~Telop();

private:
    char pad_0008[0x1F8];
};
ASSERT_SIZE(Telop, 0x200);

/**
 * @brief Class for the various selection UIs (eg. buying/selling items)
 * 
 */
class Select {
public:
    virtual ~Select();

private:
    char pad_0008[0xD58];

};
ASSERT_SIZE(Select, 0xD60);

/**
 * @brief Class for the "+ Skip" HUD element.
 */
class Skip {
public:
    virtual ~Skip();

private:
    char pad_0008[0x1C8];

};
ASSERT_SIZE(Skip, 0x1D0);

class Status {
public:
    virtual ~Status();

private:
    char pad_0008[0x348];

};
ASSERT_SIZE(Status, 0x350);

class Timer {
public:
    virtual ~Timer();

private:
    char pad_0008[0x1D8];
};
ASSERT_SIZE(Timer, 0x1E0);

class UseItem {
public:
    virtual ~UseItem();

private:
    char pad_0008[0x518]; // 0x008

};
ASSERT_SIZE(UseItem, 0x520);

class WindowManager {
public:

private:
    char pad_0000[0x60]; // 0x00
    Balloon* m_balloon; // 0x60
    Balloon* m_monosiri; // 0x68
    Caption* m_caption; // 0x70
    Telop* m_telop; // 0x78
    Explain* m_explain; // 0x80
    UseItem* m_useItem; // 0x88
    PuniCounter* m_puniCounter; // 0x90
    Timer* m_timer; // 0x98
    KpaUI* m_kpaUI; // 0xA0
    Status* m_status; // 0xA8
    Skip* m_skip; // 0xB0
    Select* m_select; // 0xB8
    class Keyboard* m_keyboard; // 0xC0
    class ToeRanking* m_toeRanking; // 0xC8
    PartySelect* m_partySelect; // 0xD0
    Incoming* m_incoming; // 0xD8
    class SaveEffect* m_saveEffect; // 0xE0
    char pad_00E8[0x38];
};
ASSERT_SIZE(WindowManager, 0x120);

} // namespace ui::hud

namespace window {

enum WINMGR_SELECT {
    WINMGR_SELECT_KEYITEM = 0x00,
    WINMGR_SELECT_ITEM = 0x01,
    WINMGR_SELECT_ITEM_DISCARD = 0x02,
    WINMGR_SELECT_BADGE = 0x03,
    WINMGR_SELECT_SHOP_SELL = 0x04,
    WINMGR_SELECT_SHOP_LEAVE = 0x05,
    WINMGR_SELECT_SHOP_RECEIVE = 0x06,
    WINMGR_SELECT_MODE_PARTYSELECT = 0x07,
    WINMGR_SELECT_MODE_PARTYUP = 0x08,
    WINMGR_SELECT_MODE_PARTYDOWN = 0x09,
    WINMGR_SELECT_MODE_MARIOLEVELUP = 0x0A,
    WINMGR_SELECT_MODE_MARIOLEVELDOWN = 0x0B,
    WINMGR_SELECT_MODE_BADGEBUY = 0x0C,
    WINMGR_SELECT_MODE_BADGESELL = 0x0D,
    WINMGR_SELECT_MODE_BADGECHANGE = 0x0E,
    WINMGR_SELECT_MODE_BOTTAKURUCHANGE = 0x0F,
    WINMGR_SELECT_MODE_BOTTAKURU100 = 0x10,
    WINMGR_SELECT_MODE_BOTTAKURU_WIN = 0x11,
    WINMGR_SELECT_MODE_BOTTAKURU_DOU = 0x12,
    WINMGR_SELECT_MODE_BTERESACHANGE = 0x13,
    WINMGR_SELECT_MODE_JOHOYAPERFECT = 0x14,
    WINMGR_SELECT_MODE_LUIGI = 0x15,
    WINMGR_SELECT_MODE_SEVENWONDERS = 0x16,
    WINMGR_SELECT_MODE_MOKORIM = 0x17,
    WINMGR_SELECT_MODE_JOHOYAETI = 0x18,
    WINMGR_SELECT_ITEM_COOK = 0x19,
    WINMGR_SELECT_MODE_QUEST = 0x1A,
    WINMGR_SELECT_MODE_ACMASTER = 0x1B,
    WINMGR_SELECT_MODE_DISCARD = 0x1C
};

} // window

} // namespace ui