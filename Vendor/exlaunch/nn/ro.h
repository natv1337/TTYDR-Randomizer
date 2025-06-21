#pragma once

#include "lib/nx/types.h"

namespace nn::ro {

Result LookupSymbol(uintptr_t* pOutAddress, const char* name);

}