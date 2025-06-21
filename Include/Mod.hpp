#pragma once

#include <memory>

struct ModSettings {
    bool RandomizeFieldItems;
    bool RandomizeBlockAndChestItems;
    bool RandomizeEnemyItems;
};

class Mod {
public:
    Mod();
    ~Mod() = default;

    void setupGameHooks();
    
    ModSettings& getSettings() { return m_settings; }

private:
    ModSettings m_settings;

};

static inline std::unique_ptr<Mod> g_mod = std::make_unique<Mod>();