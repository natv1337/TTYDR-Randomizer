/**
 * @file Util.hpp
 * @brief Utility function definitions
 */
#pragma once

#include "Types.hpp"

#include "SDK/Wld/WldItem.hpp"
#include "SDK/Wld/WldData.hpp"

#include <utility>

namespace Util {
/**
 * @brief Gets the address of the application's main module.
 * @return uintptr_t Address of main module.
 */
uintptr_t getBaseAddress();

/**
 * @brief Checks if the item ID is allowed to be used as a random item.
 * @param itemData Item ID
 * @return bool If the randomly selected item can be used without issues.
 */
bool isItemAllowedForRandomizer(wld::fld::data::ItemData* itemData);

/**
 * @brief Checks if an item should get randomized to prevent items important for progression from getting randomized.
 * @param id Item ID.
 * @return bool If the item ID is safe to randomize.
 */
bool shouldItemBeRandomized(const char* id);

/**
 * @brief Gets a random signed integer between a lower and upper bound (inclusive).
 * @param lowerBound Minimum value to generate.
 * @param upperBound Maximum value to generate.
 * @return s32 Random integer.
 */
s32 getRandomNumberInRange(s32 lowerBound, s32 upperBound);

/**
 * @brief Gets a random item ID from the data_character_item.elf file.
 * @return char* Pointer to item ID.
 */
char* getRandomItemId();

s32 getRandomItemIndex();

bool isItemKindBadge(wld::fld::item::ItemKind kind);

s32 getRandomBadgeItemIndex();

wld::fld::data::ItemData* getItemDataArray();

bool isIpv4AddressValid(const char* address);

/**
 * @brief Calls a function using a pointer and arguments.
 * @tparam TRet Function return type.
 * @tparam TArgs Function parameter types.
 * @param offset Offset to function relative to application's executable base address.
 * @param args Parameters for the function.
 * @return TRet Function return type.
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

#define ASSERT_SIZE(t, offset) static_assert(sizeof(t) == offset, "Incorrect size for " #t " (should be " #offset ").")

#define STRUCT_ALIGN(align) \
    __attribute__((aligned(align)))
