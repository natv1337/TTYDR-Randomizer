#pragma once

#include "Types.hpp"
#include "result.hpp"

namespace nn::fs {

enum OpenMode {
    OpenMode_Read = 1 << 0,
    OpenMode_Write = 1 << 1,
    OpenMode_Append = 1 << 2
};

enum WriteOptionFlag {
    WriteOptionFlag_Flush = 1 << 0,
};

enum DirectoryEntryType {
    DirectoryEntryType_Directory,
    DirectoryEntryType_File
};

struct FileHandle {
    u64 _internal;
};

nn::Result CreateFile(const char* path, s64 size);
nn::Result OpenFile(FileHandle* outHandle, const char* path, OpenMode mode);
void CloseFile(FileHandle handle);
nn::Result WriteFile(FileHandle handle, s64 position, const void* buffer, u64 size, const WriteOptionFlag& opt);

nn::Result MountSdCardForDebug(const char* mount);
  
nn::Result GetEntryType(nn::fs::DirectoryEntryType*, const char*);

nn::Result DeleteFile(const char*);

} // namespace nn::fs
