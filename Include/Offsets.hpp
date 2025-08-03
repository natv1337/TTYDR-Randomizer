/**
 * @file Offsets.hpp
 * @brief Various offsets for functions and static variables relative to the executable's base address.
 */
#pragma once

#include <stddef.h>

namespace Offsets {

// Offset to an ingame allocation function.
inline constexpr ptrdiff_t s_ingameAllocate = 0x313828;

// Offset to an ingame free function.
inline constexpr ptrdiff_t s_ingameFree = 0x305D74;

// Offset to a pointer to an allocator used by the in-game allocate function.
inline constexpr ptrdiff_t s_globalAllocator = 0x25250A8;

// Offset to a helper function that converts a string to a C string.
inline constexpr ptrdiff_t s_stringTypeToCString = 0x177608;

// Offset to a helper function that copies a C string into a string.
inline constexpr ptrdiff_t s_copyCStringToStringType = 0x177244; 

// Offset to a function that compares an std::string to a cstring.
inline constexpr ptrdiff_t s_compareStringWithCString = 0x71C030;

// Offset to the std::string::rfind function.
inline constexpr ptrdiff_t s_rfindStringOffset = 0xAC1520;

// Offset to the function that is responsible for most of the game's initialization.
inline constexpr ptrdiff_t s_mainInitialization = 0x3277F0;

// Offset to the fs::Manager constructor.
inline constexpr ptrdiff_t s_fsManagerCtor = 0x303154; 

// Offset for an inline function hook that sets an item ID for an item found in the field.
inline constexpr ptrdiff_t s_fieldItemIdHook = 0x3EA814;

// Offset for an inline function hook in the wld::btl::btlunit::BTLUNIT constructor that assigns a default item ID to an enemy.
inline constexpr ptrdiff_t s_battleUnitSetItemHook = 0x44B764;

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

// Offset for a function that retrieves a pointer in an fs::Elf's data that points to the data related to a symbol.
inline constexpr ptrdiff_t s_getSymbolInElfData = 0x301FC0;

// Offset for wld::Manager static instance.
inline constexpr ptrdiff_t s_worldManager = 0x2525038;

// Offset for hid::Manager static instance.
inline constexpr ptrdiff_t s_hidManager = 0x2525058;

// Offset for an inline hook that sets item IDs for regular shops.
inline constexpr ptrdiff_t s_setupShopItemsHook = 0x67CA58;

// Offset for an inline hook that sets item IDs for the Badge Shop in Rogueport.
inline constexpr ptrdiff_t s_setBadgeShopItemsHook = 0x676E08;

// Offset for an inline hook that sets item IDs and prices for items sold by Charlieton in Rogueport.
inline constexpr ptrdiff_t s_charlietonOverworldItemsHook = 0x974E68;

// Offset for an inline hook that sets item IDs and prices for items sold by Charlieton in the Pit of 100 Trials.
inline constexpr ptrdiff_t s_charlietonPitItemsHook = 0x974EE4;

// Offset for an inline hook that sets item IDs and prices for items sold by Dazzle.
inline constexpr ptrdiff_t s_setDazzleItemsHook = 0x97411C;

// Offset for a trampoline hook that sets an item for audience members to throw.
inline constexpr ptrdiff_t s_audienceSetItemHook = 0x6D2F78;

inline constexpr ptrdiff_t s_shopDataVector = 0x25ADF68;

// Offset for GSWF static instance.
inline constexpr ptrdiff_t s_gswfManager = 0x2525090;

// Offset for fs::Manager static instance.
inline constexpr ptrdiff_t s_fsManager = 0x2525068;

} // namespace offsets