/**
 * @file Fs.hpp
 * @brief Class definitions for the fs namespace.
 */
#pragma once

#include "Offsets.hpp"
#include "../Util.hpp"

namespace fs {

class File;
class Memory;

struct Elf {
    template <typename T>
    T* findSymbol(const char* symbolName) {
        return Util::callFunction<T*, Elf*, const char*>(Offsets::s_getSymbolInElfData, this, symbolName);
    }

private:
    char pad_0000[0x60];
};
ASSERT_SIZE(Elf, 0x60);

class ElfFile {
public:
    virtual ~ElfFile();

    const char* getVirtualFileSystemName() { return &m_virtualFsDir[0]; }
    const char* getActualFileSystemName() { return &m_actualFsDir[0]; }
    const char* getCacheFileSystemName() { return &m_cacheFsDir[0]; }
    Elf& getElfData() { return m_elfData; }

private:
    char pad_0008[0x20];      // 0x0008
    char m_virtualFsDir[256]; // 0x0028
    char m_actualFsDir[256];  // 0x0128
    char m_cacheFsDir[256];   // 0x0228
    char pad_0328[0x08];      // 0x0328
    Memory* m_memory;         // 0x0330
    char pad_0338[0x08];      // 0x0338
    Elf* m_elfDataPtr;        // 0x0340
    char pad_0348[0x90];      // 0x0348
    Elf m_elfData;            // 0x03D8
};
ASSERT_SIZE(ElfFile, 0x438);

class Manager {
public:
    GET_STATIC_INSTANCE(Manager, Offsets::s_fsManager)

    bool doesFileExist(const char* fileName);

private:
    char pad_0000[0xCF70];

};
ASSERT_SIZE(Manager, 0xCF70);

} // namespace fs