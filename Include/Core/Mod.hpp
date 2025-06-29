#pragma once

#include <memory>

#define MOD_NAME "TTYDR-Randomizer"

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
    ~Mod() = default;

    static void initialize();

    /**
     * @brief
     *   Calls an in-game memory allocation function.
     * 
     * @param size 
     *   Size of memory buffer to allocate.
     * 
     * @return void*
     *   Pointer to allocated memory.
     */
    static void* allocate(size_t size);

    /**
     * @brief
     *   Calls an in-game memory deallocation function.
     * 
     * @param ptr 
     *   Pointer to memory allocated with allocate function.
     */
    static void deallocate(void* ptr);

    ModSettings& getSettings() { return m_settings; }

private:
    ModSettings m_settings;
    
};

inline std::unique_ptr<Mod> g_mod = std::make_unique<Mod>();
