/**
 * @file Wld.hpp
 * @brief Class definitions for the wld namespace.
 */
#pragma once

#include "Collision.hpp"
#include "Fs.hpp"
#include "Math.hpp"
#include "String.hpp"
#include "Util.hpp"

#include "Wld/WldBtl.hpp"
#include "Wld/WldCam.hpp"
#include "Wld/WldData.hpp"
#include "Wld/WldFld.hpp"
#include "Wld/WldRes.hpp"

namespace wld {

namespace fld {

namespace data {

struct DisposItem {
    char* MapName;        // 0x00
    char* JpIdentifier;   // 0x08
    char* ItemIdentifier; // 0x10
private:
    char pad_0018[0x80]; // 0x18
};
ASSERT_SIZE(DisposItem, 0x98);

} // namespace data

} // namespace fld

class GfxObj;

class Manager {
public:
    virtual ~Manager();

    GET_STATIC_INSTANCE(Manager, Offsets::s_worldManager)

    res::ResElf* getCharacterItem() { return reinterpret_cast<res::ResElf*>(m_characterItemData.getResource()); }

private:
    GfxObj* m_gfxObj;                                  // 0x08
    res::Manager* m_resManager;                        // 0x10
    fld::Manager* m_fldManager;                        // 0x18
    char pad_0020[0x10];                               // 0x20
    cam::Manager* m_camManager;                        // 0x30
    collision::hit::ShapeObjManager* m_shapeObjectMgr; // 0x38
    bool m_handlesInitialized;                         // 0x40
    res::ResHandle m_mapId;                            // 0x48
    res::ResHandle m_characterNpcData;                 // 0x68
    res::ResHandle m_characterPartyData;               // 0x88
    res::ResHandle m_characterMobjData;                // 0xA8
    res::ResHandle m_characterAobjData;                // 0xC8
    res::ResHandle m_characterItemData;                // 0xE8
    res::ResHandle m_npcModelData;                     // 0x108
    res::ResHandle m_playerModelData;                  // 0x128
    res::ResHandle m_mobjModelData;                    // 0x148
    res::ResHandle m_gobjModelData;                    // 0x168
    res::ResHandle m_itemModelData;                    // 0x188
    res::ResHandle m_itemlottableMapData;              // 0x1A8
    res::ResHandle m_battleModelData;                  // 0x1C8
    res::ResHandle m_uiData;                           // 0x1E8
    res::ResHandle m_actionballoonParamData;           // 0x208
    res::ResHandle m_playerParamData;                  // 0x228
    res::ResHandle m_jumpParamData;                    // 0x248
    res::ResHandle m_unknownHandle1;                   // 0x268
    res::ResHandle m_unknownHandle2;                   // 0x288
    res::ResHandle m_eventFlagData;                    // 0x2A8
    res::ResHandle m_partyhintData;                    // 0x2C8
    res::ResHandle m_fieldParamData;                   // 0x2E8
    res::ResHandle m_gobjParamData;                    // 0x308
    res::ResHandle m_gobjItemParamData;                // 0x328
    res::ResHandle m_housedoorParamData;               // 0x348
    char pad_0368[0x30];                               // 0x368
};
ASSERT_SIZE(Manager, 0x398);

} // namespace wld