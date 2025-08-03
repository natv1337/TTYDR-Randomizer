#pragma once

namespace nn::os {
struct UserExceptionInfo;
} // namespace nn::os

namespace ExceptionHandler {

void userExceptionHandler(nn::os::UserExceptionInfo* info);

} // namespace ExceptionHandler