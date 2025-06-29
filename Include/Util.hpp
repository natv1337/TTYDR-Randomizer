/**
 * @file Util.hpp
 * @brief Utility function definitions
 */
#pragma once

#include "Types.hpp"

#include <utility>

namespace Util {
/**
 * @brief
 *   Gets the address of the application's main module.
 * 
 * @return uintptr_t 
 *   Address of main module.
 */
uintptr_t getBaseAddress();

/**
 * @brief 
 *   Checks if the item ID is allowed to be used as a random item.
 * 
 * @param id 
 *   Item ID
 * 
 * @return bool
 *   If the randomly selected item can be used without issues.
 */
bool isItemAllowedForRandomizer(const char* id);

/**
 * @brief
 *   Checks if an item should get randomized to prevent items important for progression from getting randomized.
 * 
 * @param id 
 *   Item ID.
 * 
 * @return bool
 *   If the item ID is safe to randomize.
 */
bool shouldItemBeRandomized(const char* id);

/**
 * @brief 
 *   Gets a random signed integer between a lower and upper bound (inclusive).
 * 
 * @param lowerBound 
 *   Minimum value to generate.
 * 
 * @param upperBound 
 *   Maximum value to generate.
 * 
 * @return s32 
 *   Random integer.
 */
s32 getRandomNumberInRange(s32 lowerBound, s32 upperBound);

/**
 * @brief
 *   Gets a random item ID from the data_character_item.elf file.
 * 
 * @return char* 
 *   Pointer to item ID.
 */
char* getRandomItemId();

/**
 * @brief
 *   Calls a function using a pointer and arguments.
 * 
 * @tparam TRet 
 *   Function return type.
 * 
 * @tparam TArgs 
 *   Function parameter types.
 * 
 * @param offset 
 *   Offset to function relative to application's executable base address.
 * 
 * @param args 
 *   Parameters for the function.
 * 
 * @return TRet 
 *   Function return type.
 */
template <typename TRet, typename... TArgs>
TRet callFunction(uintptr_t offset, TArgs... args) {
    using tFunc = TRet (*)(TArgs...);
    auto pFunc = reinterpret_cast<tFunc>(getBaseAddress() + offset);
    return pFunc(std::forward<TArgs>(args)...);
}

} // namespace Util

#define GET_STATIC_INSTANCE(t, offset)                                                                                 \
    static t* getInstance() { return *reinterpret_cast<t**>(Util::getBaseAddress() + offset); }

#define ASSERT_SIZE(t, offset) static_assert(sizeof(t) == offset)
