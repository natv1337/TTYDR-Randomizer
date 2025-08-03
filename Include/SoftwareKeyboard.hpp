/**
 * @file SoftwareKeyboard.hpp
 * @brief Definition for SoftwareKeyboard class.
 */
#pragma once

#include "nnSdk/swkbd.hpp"

enum class EncodingMode {
    UTF8,
    UTF16
};

class SoftwareKeyboard {
public:
    explicit SoftwareKeyboard(EncodingMode encodingMode);
    ~SoftwareKeyboard();

    void setHeaderText(const char* headerText);
    void setGuideText(const char* guideText);
    void setSubText(const char* subText);

    void setHeaderText(const char16_t* headerText);
    void setGuideText(const char16_t* guideText);
    void setSubText(const char16_t* subText);

    void setTextCheckCallback(nn::swkbd::TextCheckCallback callback);

    void setBlurBackground(bool enabled) { m_keyboardArg.Config.IsUseBlurBackground = enabled; }
    void setCancelButtonDisabled(bool enabled) { m_keyboardArg.Config.IsCancelButtonDisabled = enabled; }
    void setUsePrediction(bool enabled) { m_keyboardArg.Config.IsPredictionEnabled = enabled; }

    void setInputTextMinLength(s32 length) { m_keyboardArg.Config.TextMinLength = length; }
    void setInputTextMaxLength(s32 length) { m_keyboardArg.Config.TextMaxLength = length; }

    bool showKeyboard();
    bool isCancelled() { return m_cancelled; }

    const char* getTextUtf8() { return reinterpret_cast<const char*>(m_keyboardOutput.Buffer); }
    const char16_t* getTextUtf16() { return reinterpret_cast<const char16_t*>(m_keyboardOutput.Buffer); }

private:
    void initializeKeyboard();
    void initializeTextCheckBuffer();
    void initializeWorkBuffer();
    void initializeStringBuffer();

    bool isUtf8() { return m_keyboardArg.Config.IsUseUtf8; }

private:
    nn::swkbd::ShowKeyboardArg m_keyboardArg;
    nn::swkbd::String m_keyboardOutput;
    bool m_cancelled = false;

};
