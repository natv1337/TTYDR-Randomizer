/**
 * @file String.hpp
 * @brief String class definition.
 */
#pragma once

#include "../Util.hpp"

#include <stddef.h>

/**
 * @brief Recreation of std::string type used in-game.
 * 
 */
class String {
public:
    bool compare(const char* str);
    const char* getCString();
    size_t length() const;
    void assign(const char* str);

    // Gets the position of the last occurance of a character
    size_t rfind(char ch);

private:
    bool isShortString() const { return (m_shortString.Tag & 1) == 0; }

private:
    // Underlying data for type.
    union {
        struct {
            u8 Tag;
            char Data[15];
        } m_shortString;

        struct {
            u64 Tag;
            size_t Length;
            const char* Data;
        } m_longString;
    };
};
ASSERT_SIZE(String, 0x18);
