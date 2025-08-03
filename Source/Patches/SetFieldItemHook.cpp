#include "Patches/SetFieldItemHook.hpp"

#include "SDK/Wld.hpp"
#include "Core/Logger.hpp"

void SetFieldItemHook::Callback(exl::hook::InlineCtx* ctx) {
    auto fieldItem = reinterpret_cast<wld::fld::data::DisposItem*>(ctx->X[8]);
    if (!Util::shouldItemBeRandomized(fieldItem->ItemIdentifier)) {
        return;
    }

    fieldItem->ItemIdentifier = Util::getRandomItemId();
}