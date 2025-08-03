#pragma once

#include "Types.hpp"
#include "result.hpp"
#include "stddef.h"

namespace nn::fs {

struct FileHandle {
    u64 _internal;
};

enum DirectoryEntryType {
    DirectoryEntryType_Directory,
    DirectoryEntryType_File,
};

enum WriteOptionFlag {
    WriteOptionFlag_Flush = 1 << 0,
};

struct WriteOption {
    int flags;
    static WriteOption CreateOption(int flags) {
        return {
            .flags = flags,
        };
    }
};

enum OpenMode {
    OpenMode_Read   = 1 << 0,
    OpenMode_Write  = 1 << 1,
    OpenMode_Append = 1 << 2,

    OpenMode_ReadWrite  = OpenMode_Read | OpenMode_Write,
};

Result CreateFile(const char* path, s64 size);
Result OpenFile(FileHandle* outHandle, char const* path, int mode);
Result DeleteFile(const char* path);
void CloseFile(FileHandle handle);

Result WriteFile(FileHandle handle, s64 position, const void* buffer, u64 size, const WriteOption& option);

Result SetFileSize(FileHandle handle, s64 size);

Result MountSdCardForDebug(const char* mount);

Result GetEntryType(DirectoryEntryType* out, const char* path);

} // namespace nn::fs
