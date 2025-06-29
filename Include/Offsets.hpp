/**
 * @file Offsets.hpp
 * @brief Various offsets for functions and static variables relative to the executable's base address.
 */
#pragma once

#include <stddef.h>

namespace Offsets {

// Offset to an ingame allocation function.
inline constexpr ptrdiff_t s_ingameAllocate = 0x305D58;

// Offset to an ingame free function.
inline constexpr ptrdiff_t s_ingameFree = 0x305D74;

// Offset to a helper function that converts a string to a C string.
inline constexpr ptrdiff_t s_stringTypeToCString = 0x177608;

// Offset to a helper function that copies a C string into a string.
inline constexpr ptrdiff_t s_copyCStringToStringType = 0x177244; 

// Offset to the function that is responsible for most of the game's initialization.
inline constexpr ptrdiff_t s_mainInitialization = 0x3277F0;

// Offset to the fs::Manager constructor.
inline constexpr ptrdiff_t s_fsManagerCtor = 0x303154; 

// Offset for an inline function hook that sets an item ID for an item found in the field.
inline constexpr ptrdiff_t s_fieldItemIdHook = 0x3EA814;

// Offset for an inline function hook in the wld::btl::btlunit::BTLUNIT constructor that assigns a default item ID to an enemy.
inline constexpr ptrdiff_t s_battleUnitSetItemHook = 0x44B6C0;

// Offset for the item::EntryDropForMobj function 
inline constexpr ptrdiff_t s_itemDropForMobjHook = 0x603B50;

// Offset for an inline function hook that sets an item ID for a shop item entry.
inline constexpr ptrdiff_t s_shopItemIdHook = 0x67CA1C;

// Offset for an inline function hook that sets a shop item's price.
inline constexpr ptrdiff_t s_shopItemPriceHook = 0x67CA2C;

// Offset to a helper function that returns a pointer to a wld::fld::data::ItemData type when supplied with an item ID.
inline constexpr ptrdiff_t s_getItemDataFromId = 0x55B650;

// Offset for a function that assists in calculating damage.
inline constexpr ptrdiff_t s_damageCheckHook1 = 0x466D70;

// Offset for another function that assists in calculating damage.
inline constexpr ptrdiff_t s_damageCheckHook2 = 0x467320;

} // namespace offsets