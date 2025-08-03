#pragma once

#include "SDK/Gfx/GfxCam.hpp"

namespace wld::cam {

class Manager : public gfx::cam::Viewproj {
public:
    virtual ~Manager() override;

private:
    char pad_0218[0x108];
};
ASSERT_SIZE(Manager, 0x320);

} // namespace wld::cam