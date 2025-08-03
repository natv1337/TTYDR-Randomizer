#pragma once

#include "exlaunch/lib.hpp"

namespace fs {
class Manager;
}

HOOK_DEFINE_TRAMPOLINE(FsManagerCtorHook) {

/**
 * @brief 
 *   fs::Manager::Manager hook callback.
 * 
 * @param thisp
 *   [X0] Global file system manager pointer. 
 * 
 */
static void Callback(fs::Manager* thisp);

};