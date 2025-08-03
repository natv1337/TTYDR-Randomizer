#pragma once

#include "../../Util.hpp"

namespace gfx::cam {

class Viewproj {
public:
    virtual ~Viewproj();

private:
    char pad_0008[0x210];
};
ASSERT_SIZE(Viewproj, 0x218);

} // namespace gfx::cam