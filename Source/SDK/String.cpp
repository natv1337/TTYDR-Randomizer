#include "SDK/String.hpp"

#include "Offsets.hpp"

void String::assign(const char* str) {
    Util::callFunction<void, String*, const char*>(Offsets::s_copyCStringToStringType, this, str);
}

const char* String::getCString() {
    if (isShortString()) {
        return &m_shortString.Data[0];
    }

    return m_longString.Data;
}

bool String::compare(const char* str) {
    return Util::callFunction<bool, String*, const char*>(Offsets::s_compareStringWithCString, this, str);
}

size_t String::length() const {
    return isShortString() ? m_shortString.Tag >> 1 : m_longString.Length;
}

size_t String::rfind(char ch) {
    return Util::callFunction<size_t, String*, char, size_t>(Offsets::s_rfindStringOffset, this, ch, -1);
}