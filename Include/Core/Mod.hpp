#pragma once

#include <memory>
#include "../Util.hpp"

#define MOD_NAME "TTYDR-Randomizer"
#define LOG_FILE_OUTPUT "sd:/RandomizerOutput.txt"
#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
#define USE_FILE_LOGGER
#define USE_FTP_LOGGER
#endif

class Logger;

struct ModSettings {
    const char* ModName;
    bool RandomizeFieldItems;
    bool RandomizeBlockAndChestItems;
    bool RandomizeEnemyItems;
    bool RandomizeShopItems;
};

class Mod {
public:
    Mod();
    ~Mod();

    Mod(const Mod&) = delete;
    Mod& operator=(const Mod&) = delete;
    Mod(Mod&&) = delete;
    Mod& operator=(Mod&&) = delete;

    static void initialize();

    /**
     * @brief Calls an in-game memory allocation function.
     * @note Should be used if you need any heap allocated data to use with the nnSdk.
     * @param size Size of memory to allocate.
     * @param alignment Alignment of memory.
     * @return void* Pointer to allocated memory.
     */
    static void* allocate(size_t size, s32 alignment = 0x10);

    /**
     * @brief Calls an in-game memory deallocation function.
     * @param ptr Pointer to memory allocated with allocate function.
     */
    static void deallocate(void* ptr);

    ModSettings& getSettings() { return m_settings; }

    void mountSdCard();
    
    const bool isSdCardMounted() const { return m_isSdCardMounted; }

private:
    Logger* m_logger = nullptr;
    ModSettings m_settings;
    bool m_isSdCardMounted = false;
    
};

inline std::unique_ptr<Mod> g_mod = std::make_unique<Mod>();

#define ALLOCATE(size) \
    Mod::allocate(size)

#define ALLOCATE_ALIGNED(size, align) \
    Mod::allocate(size, align)

#define DEALLOCATE(ptr) \
    Mod::deallocate(ptr)
