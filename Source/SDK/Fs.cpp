#include "SDK/Fs.hpp"

bool fs::Manager::doesFileExist(const char* fileName) {
    return Util::callFunction<bool, fs::Manager*, const char*>(0x303E18, this, fileName);
}