#include "SDK/Wld/WldFld.hpp"

wld::fld::data::ItemData* wld::fld::getItemDataArray() {
    return Util::callFunction<wld::fld::data::ItemData*>(0x400200);
}

wld::fld::data::Parameter* wld::fld::getParameter(const char* param, s32 offset) {
    return Util::callFunction<wld::fld::data::Parameter*, const char*, s32>(0xaa6c70, param, offset);
}

float wld::fld::getFloatParameter(const char* param, s32 offset) {
    wld::fld::data::Parameter* parameter = wld::fld::getParameter(param, offset);
    if (!parameter) {
        return 0.0f;
    }

    return parameter->FloatValue;
}

char* wld::fld::getStringParameter(const char* param, s32 offset) {
    wld::fld::data::Parameter* parameter = wld::fld::getParameter(param, offset);
    if (!parameter) {
        return "";
    }

    return parameter->StringValue;
}