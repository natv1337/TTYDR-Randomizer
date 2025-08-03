#pragma once

#include "Types.hpp"

struct in_addr {
    u32 data;
};

struct sockaddr {
    u8 _0;
    u8 family;
    u16 port;
    in_addr address;
    u8 _8[8];
};

struct hostent {
    char*   h_name;
    char**  h_aliases;
    int     h_addrtype;
    int     h_length;
    char**  h_addr_list;
};

namespace nn::socket {



struct Config {
    int unkInt1 = 2; // 0x0 (value is 2 in SMO sdk, 8 in sv)
    bool unkBool1 = false; // 0x4
    bool isUseBsdS = false; // 0x5
    void* Pool; // 0x8
    u64 PoolSize; // 0x10
    u64 AllocPoolSize; // 0x18
    u64 unkLong1 = 0x8000; // 0x20
    u64 unkLong2 = 0x10000; // 0x28
    u64 unkLong3 = 0x30000; // 0x30
    u64 unkLong4 = 0x30000; // 0x38
    u64 unkLong5 = 0x2400; // 0x40
    u64 unkLong6 = 0xA500; // 0x48
    int unkInt3 = 4; // 0x50
    int ConcurLimit; // 0x54
    int padding;
};
static_assert(sizeof(Config) == 0x60, "Config Size");

Result Initialize(void* pool, u64 poolSize, u64 allocPoolSize, int concurLimit);
Result Initialize(const Config& config);

s32 Socket(s32 domain, s32 type, s32 protocol);
s32 SetSockOpt(s32 socket, s32 socketLevel, s32 option, const void*, u32 len);

s32 Connect(s32 socket, const sockaddr* address, u32 addressLen);
Result Close(s32 socket);
s32 Send(s32 socket, const void* data, u64 dataLen, s32 flags);
s32 Recv(s32 socket, void* out, u64 outLen, s32 flags);

u16 InetHtons(u16 val);
s32 InetAton(const char* addressStr, in_addr* addressOut);
int InetPton(int, const char*, void*);

hostent* GetHostByName(const char* name);
u32 GetLastErrno();

}