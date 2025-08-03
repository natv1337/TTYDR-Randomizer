#include "Core/Logger.hpp"

#include "Core/Mod.hpp"

#include "nnSdk/nifm.hpp"
#include "nnSdk/socket.hpp"
#include "nnSdk/time.hpp"
#include "nnSdk/util.hpp"

#define KILOBYTE_SIZE 1024

namespace {
constexpr inline int g_defaultTcpMaxBufferSize      = 192 * KILOBYTE_SIZE; // 192kb
constexpr inline int g_minTransferMemorySize        = ((2 * g_defaultTcpMaxBufferSize) + (128 * KILOBYTE_SIZE)); // 512kb
constexpr inline int g_minSocketAllocatorSize       = 128 * KILOBYTE_SIZE; // 128kb

constexpr inline auto g_socketAllocatorSize = g_minSocketAllocatorSize * 1;
constexpr inline auto g_transferMemorySize = g_minTransferMemorySize * 1;

constexpr inline auto g_socketPoolSize = g_minSocketAllocatorSize + g_minTransferMemorySize;
};
char g_socketPool[g_socketPoolSize] __attribute__((aligned(0x4000)));

Logger* Logger::s_instance;

Logger::Logger(const char* outputPath) {
    s_instance = this;
    m_fileLoggerState.OutputPath = outputPath;
}

Logger::~Logger() {
    if (m_fileLoggerState.Initialized) {
        nn::fs::CloseFile(m_fileLoggerState.Handle);
    }
}

void Logger::log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[0x500];
    s32 fmtCount = nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args);

    va_end(args);

    if (fmtCount <= 0) {
        return;
    }

    nn::time::PosixTime posixTime;
    nn::time::StandardUserSystemClock::GetCurrentTime(&posixTime);

    nn::time::CalendarTime calendarTime;
    nn::time::CalendarAdditionalInfo calendarAdditional;
    nn::time::ToCalendarTime(&calendarTime, &calendarAdditional, posixTime);
    
    char finalBuffer[0x600];
    fmtCount = nn::util::SNPrintf(
        finalBuffer, 
        sizeof(finalBuffer), 
        "[%d-%d-%d %d:%d:%d] %s\n",
        calendarTime.Year,
        calendarTime.Month,
        calendarTime.Day,
        calendarTime.Hour,
        calendarTime.Minute,
        calendarTime.Second,
        buffer
    );

    if (fmtCount <= 0);

    logToFile(finalBuffer, fmtCount);
    logToFtp(finalBuffer, fmtCount);
}

void Logger::initializeFileLogger() {
    if (!g_mod->isSdCardMounted()) {
        return;
    }

    nn::fs::DirectoryEntryType type;
    s32 result = nn::fs::GetEntryType(&type, m_fileLoggerState.OutputPath);

    if (type == nn::fs::DirectoryEntryType_Directory) {
        return;
    }

    if (type == nn::fs::DirectoryEntryType_File) {
        nn::fs::DeleteFile(m_fileLoggerState.OutputPath);
    }
    result = nn::fs::CreateFile(m_fileLoggerState.OutputPath, 0);

    if (result == 0) {
        m_fileLoggerState.Initialized = true;
    }
}

void Logger::logToFile(const void* buffer, size_t bufferSize) {
    if (!m_fileLoggerState.Initialized) {
        return;
    }

    nn::fs::OpenFile(
        &m_fileLoggerState.Handle, 
        m_fileLoggerState.OutputPath, 
        nn::fs::OpenMode_ReadWrite | nn::fs::OpenMode_Append
    );

    nn::fs::SetFileSize(m_fileLoggerState.Handle, m_fileLoggerState.Offset + bufferSize);
    nn::fs::WriteFile(
        m_fileLoggerState.Handle,
        m_fileLoggerState.Offset,
        buffer,
        bufferSize,
        nn::fs::WriteOption::CreateOption(nn::fs::WriteOptionFlag_Flush)
    );

    nn::fs::CloseFile(m_fileLoggerState.Handle);

    m_fileLoggerState.Offset += bufferSize;
}

void Logger::initializeFtpLogger(const char* ipAddress) {
    in_addr hostAddress = { 0 };
    sockaddr serverAddress;

    nn::nifm::Initialize();
    nn::nifm::SubmitNetworkRequest();

    while (nn::nifm::IsNetworkRequestOnHold()) {}

    if (!nn::nifm::IsNetworkAvailable()) {
        m_ftpLoggerState.Unavailable = true;
        return;
    }

    nn::socket::Config config;
    config.Pool = g_socketPool;
    config.AllocPoolSize = g_socketAllocatorSize;
    config.PoolSize = g_socketPoolSize;
    config.ConcurLimit = 0xE;

    nn::socket::Initialize(config);

    if ((m_ftpLoggerState.FileDescriptor = nn::socket::Socket(2, 1, 0)) < 0) {
        m_ftpLoggerState.Unavailable = true;
        return;
    }

    nn::socket::InetAton(ipAddress, &hostAddress);
    serverAddress.address = hostAddress;
    serverAddress.port = nn::socket::InetHtons(static_cast<u64>(3080));
    serverAddress.family = 2;

    Result result = nn::socket::Connect(m_ftpLoggerState.FileDescriptor, &serverAddress, sizeof(serverAddress));

    m_ftpLoggerState.Initialized = result == 0;

}

void Logger::logToFtp(const void* buffer, size_t bufferSize) {
    if (!m_ftpLoggerState.Initialized || m_ftpLoggerState.Unavailable) {
        return;
    }

    nn::socket::Send(m_ftpLoggerState.FileDescriptor, buffer, bufferSize, 0);
}