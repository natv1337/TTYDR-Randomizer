#pragma once

#include "Util.hpp"

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