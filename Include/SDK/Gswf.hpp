#pragma once

#include "../Util.hpp"

#include "Offsets.hpp"

// Is actually just an std::unordered map
class Gswf {
public:
    s32 getGsTableValue(const char* key);

    GET_STATIC_INSTANCE(Gswf, Offsets::s_gswfManager)
};