#pragma once

#include "exlaunch/lib.hpp"

#include "SDK/Math.hpp"
#include "SDK/Wld/WldItem.hpp"

class String;
namespace wld::fld::mobj {
class MobjHandle;
}

HOOK_DEFINE_TRAMPOLINE(EntryDropForMobjHook) {

static wld::fld::item::ItemHandle Callback(
    String* name, 
    String* identifier, 
    math::Vec3& pos, 
    wld::fld::mobj::MobjHandle* mobj
);

};