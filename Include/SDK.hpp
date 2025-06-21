#pragma once

#include "Types.hpp"
#include "Util.hpp"

namespace collision::hit {

class ShapeObjectManager;

} // namespace collision::hit

namespace fs {

struct Elf {
    template <typename T>
    T* findSymbol(const char* symbolName) {
        typedef T* (*tFindSymbolFromElf)(Elf*, const char*);
        auto pFindSymbolFromElf = reinterpret_cast<tFindSymbolFromElf>(Util::getBaseAddress() + 0x301fc0);

        return pFindSymbolFromElf(this, symbolName);
    }

private:
    char pad_0000[0x60];
};

class ElfFile {
public:
    virtual ~ElfFile();

    Elf& getElfData() { return m_elfData; }

private:
    char pad_0008[0x3D0]; // 0x08
    Elf m_elfData;        // 0x3D8
};

} // namespace fs

namespace util {

class HandleBase {
public:
    virtual ~HandleBase();

private:
    u64 m_identifier;
    u64 m_unk1;
};
static_assert(sizeof(HandleBase) == 0x18);

template <typename T>
class Handle : public HandleBase {
public:
    virtual ~Handle();

    T* getResource() { return m_resource; }

private:
    T* m_resource;
};
static_assert(sizeof(Handle<void>) == 0x20);

} // namespace util

namespace wld {

class GfxObj;

namespace cam {

class Manager;

} // namespace wld::cam

namespace fld {

class Manager;

} // namespace wld::fld

namespace res {

class ResElf {
public:
    virtual ~ResElf();

    fs::ElfFile* getElfFile() { return m_elfFile; }

private:
    char pad_0008[0x120];   // 0x08
    fs::ElfFile* m_elfFile; // 0x128
};
static_assert(sizeof(ResElf) == 0x130);

class ResHandle : public util::Handle<ResElf> {
public:
    virtual ~ResHandle();
};
static_assert(sizeof(ResHandle) == 0x20);

class Manager;

} // namespace wld::res

class Manager {
public:
    virtual ~Manager();

    static Manager* getInstance() { return *reinterpret_cast<Manager**>(Util::getBaseAddress() + 0x2525038); }

    res::ResElf* getCharacterItem() { return m_characterItemData.getResource(); }

private:
    GfxObj* m_gfxObj;                                     // 0x08
    res::Manager* m_resManager;                           // 0x10
    fld::Manager* m_fldManager;                           // 0x18
    char pad_0020[0x10];                                  // 0x20
    cam::Manager* m_camManager;                           // 0x30
    collision::hit::ShapeObjectManager* m_shapeObjectMgr; // 0x38
    bool m_handlesInitialized;                            // 0x40
    res::ResHandle m_mapId;                               // 0x48
    res::ResHandle m_characterNpcData;                    // 0x68
    res::ResHandle m_characterPartyData;                  // 0x88
    res::ResHandle m_characterMobjData;                   // 0xA8
    res::ResHandle m_characterAobjData;                   // 0xC8
    res::ResHandle m_characterItemData;                   // 0xE8
    res::ResHandle m_npcModelData;                        // 0x108
    res::ResHandle m_playerModelData;                     // 0x128
    res::ResHandle m_mobjModelData;                       // 0x148
    res::ResHandle m_gobjModelData;                       // 0x168
    res::ResHandle m_itemModelData;                       // 0x188
    res::ResHandle m_itemlottableMapData;                 // 0x1A8
    res::ResHandle m_battleModelData;                     // 0x1C8
    res::ResHandle m_uiData;                              // 0x1E8
    res::ResHandle m_actionballoonParamData;              // 0x208
    res::ResHandle m_playerParamData;                     // 0x228
    res::ResHandle m_jumpParamData;                       // 0x248
    res::ResHandle m_unknownHandle1;                      // 0x268
    res::ResHandle m_unknownHandle2;                      // 0x288
    res::ResHandle m_eventFlagData;                       // 0x2A8
    res::ResHandle m_partyhintData;                       // 0x2C8
    res::ResHandle m_fieldParamData;                      // 0x2E8
    res::ResHandle m_gobjParamData;                       // 0x308
    res::ResHandle m_gobjItemParamData;                   // 0x328
    res::ResHandle m_housedoorParamData;                  // 0x348
    char pad_0368[0x30];                                  // 0x368
};
static_assert(sizeof(Manager) == 0x398);

namespace fld::data {

struct DisposItem {
    char* MapName;        // 0x00
    char* JpIdentifier;   // 0x08
    char* ItemIdentifier; // 0x10
private:
    char pad_0018[0x80]; // 0x18
};
static_assert(sizeof(DisposItem) == 0x98);

struct ItemData {
    char* Identifier;   // 0x00
    char* JpIdentifier; // 0x08
private:
    char pad_0010[0x90];
};
static_assert(sizeof(ItemData) == 0xA0);

} // namespace fld::data

} // namespace wld