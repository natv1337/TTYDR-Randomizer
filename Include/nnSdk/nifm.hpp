#pragma once

#include "result.hpp"

namespace nn::nifm {

Result Initialize();
void SubmitNetworkRequest();
bool IsNetworkRequestOnHold();
bool IsNetworkAvailable();

} // namespace nn::nifm