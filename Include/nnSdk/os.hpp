#pragma once

#include "Types.hpp"

namespace nn::os {

enum UserExceptionType {
    UserExceptionType_None,
    UserExceptionType_InvalidInstructionAccess = 256,
    UserExceptionType_InvalidDataAccess = 257,
    UserExceptionType_UnalignedIstructionAccess = 258,
    UserExceptionType_UnalignedDataAccess = 259,
    UserExceptionType_UndefinedInstruction = 260,
    UserExceptionType_ExceptionalInstruction = 261,
    UserExceptionType_MemorySystemError = 262,
    UserExceptionType_FloatingPointException = 512,
    UserExceptionType_InvalidSystemCall = 769
};

union CpuRegister {
    u64 X;
    u32 W;
    u32 R;
};

union FpuRegister {
    s128 V;
    double D;
    float S;
};

struct UserExceptionInfo {
    UserExceptionType ExceptionType;
    u32 Padding[3];

    CpuRegister Registers[29];
    CpuRegister FP;
    CpuRegister LR;
    CpuRegister SP;
    CpuRegister PC;

    u64 Padding2;

    FpuRegister FpuRegisters[32];
};

void SetUserExceptionHandler(void (*)(UserExceptionInfo*), void*, u64, UserExceptionInfo*);
u32 GetCurrentCoreNumber();

} // namespace nn::os

inline const char* getUserExceptionTypeString(nn::os::UserExceptionType type) {
    switch (type) {
    case nn::os::UserExceptionType_InvalidInstructionAccess:
        return "Invalid Instruction Access";
    case nn::os::UserExceptionType_InvalidDataAccess:
        return "Invalid Data Access";
    case nn::os::UserExceptionType_UnalignedIstructionAccess:
        return "Unaligned Instruction Access";
    case nn::os::UserExceptionType_UnalignedDataAccess:
        return "Unaligned Data Access";
    case nn::os::UserExceptionType_UndefinedInstruction:
        return "Undefined Instruction";
    case nn::os::UserExceptionType_ExceptionalInstruction:
        return "Exceptional Instructoin";
    case nn::os::UserExceptionType_MemorySystemError:
        return "Memory System Error";
    case nn::os::UserExceptionType_FloatingPointException:
        return "Floating Point Exception";
    case nn::os::UserExceptionType_InvalidSystemCall:
        return "Invalid System Call";
    default:
        return "Unknown";
    }
}