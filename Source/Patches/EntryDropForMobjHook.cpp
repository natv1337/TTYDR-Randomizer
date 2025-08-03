#include "Patches/EntryDropForMobjHook.hpp"

#include "Util.hpp"
#include "SDK/String.hpp"
#include "Core/Logger.hpp"

using namespace wld::fld;

item::ItemHandle EntryDropForMobjHook::Callback(String* name, String* identifier, math::Vec3& pos, mobj::MobjHandle* mobj) {
    if (!Util::shouldItemBeRandomized(name->getCString())) {
        return Orig(name, identifier, pos, mobj);
    }

    char* newItemId = Util::getRandomItemId();
    LOG("[EntryDropForMobjHook::Callback] %s -> %s", name->getCString(), newItemId);

    name->assign(newItemId);
    identifier = name;
    return Orig(name, identifier, pos, mobj);
}