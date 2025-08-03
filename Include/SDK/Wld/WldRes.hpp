#pragma once

#include "../../Util.hpp"
#include "../Fs.hpp"
#include "../Util.hpp"

namespace wld::res {

class Manager;

class Res {};

class ResElf {
public:
    virtual ~ResElf();

    fs::ElfFile* getElfFile() { return m_elfFile; }

private:
    char pad_0008[0x120];
    fs::ElfFile* m_elfFile;
};
ASSERT_SIZE(ResElf, 0x130);

class ResHandle : public util::Handle<Res> {
public:
    virtual ~ResHandle() override;
};
ASSERT_SIZE(ResHandle, 0x20);

}