#pragma once

#include "nnSdk/fs.hpp"

class Logger {
public:
    struct FileLoggerState {
        const char* OutputPath;
        nn::fs::FileHandle Handle;
        s64 Offset = 0;
        bool Initialized = false;
    };

    struct FtpLoggerState {
        s32 FileDescriptor;
        bool Unavailable = false;
        bool Initialized = false;
    };

    Logger(const char* outputPath);
    ~Logger();

    static Logger& getLogger() { return *s_instance; }

    void log(const char* fmt, ...);

    void initializeFileLogger();
    void initializeFtpLogger(const char* ipAddress);

private:
    void logToFile(const void* buffer, size_t bufferSize);
    void logToFtp(const void* buffer, size_t bufferSize);

private:
    static Logger* s_instance;

private:
    FileLoggerState m_fileLoggerState;
    FtpLoggerState m_ftpLoggerState;

};

#ifdef MOD_DEBUG
    #define LOG(fmt, ...) Logger::getLogger().log(fmt, __VA_ARGS__)
#else
    #define LOG(fmt, ...) ((void)0)
#endif