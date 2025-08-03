#include "SoftwareKeyboard.hpp"

#include "Types.hpp"
#include "Util.hpp"
#include "nnSdk/oe.hpp"

#include "Core/Mod.hpp"

#include <string.h>
#include <array>

SoftwareKeyboard::SoftwareKeyboard(EncodingMode encodingMode) {
    initializeKeyboard(); 
    m_keyboardArg.Config.IsUseUtf8 = encodingMode == EncodingMode::UTF8;
    setBlurBackground(true);
}

SoftwareKeyboard::~SoftwareKeyboard() {
    DEALLOCATE(m_keyboardArg.TextCheckWorkBuffer);
    DEALLOCATE(m_keyboardArg.WorkBuffer);
    DEALLOCATE(m_keyboardOutput.Buffer);
}

void SoftwareKeyboard::setHeaderText(const char* headerText) {
    if (!isUtf8()) {
        return;
    }

    nn::swkbd::SetHeaderTextUtf8(&m_keyboardArg.Config, headerText);
}

void SoftwareKeyboard::setGuideText(const char* guideText) {
    if (!isUtf8()) {
        return;
    }

    nn::swkbd::SetGuideTextUtf8(&m_keyboardArg.Config, guideText);
}

void SoftwareKeyboard::setSubText(const char* subText) {
    if (!isUtf8()) {
        return;
    }

    nn::swkbd::SetGuideTextUtf8(&m_keyboardArg.Config, subText);
}

void SoftwareKeyboard::setHeaderText(const char16_t* headerText) {
    if (isUtf8()) {
        return;
    }

    nn::swkbd::SetHeaderText(&m_keyboardArg.Config, headerText);
}

void SoftwareKeyboard::setGuideText(const char16_t* guideText) {
    if (isUtf8()) {
        return;
    }

    nn::swkbd::SetGuideText(&m_keyboardArg.Config, guideText);
}

void SoftwareKeyboard::setSubText(const char16_t* subText) {
    if (isUtf8()) {
        return;
    }

    nn::swkbd::SetSubText(&m_keyboardArg.Config, subText);
}

void SoftwareKeyboard::setTextCheckCallback(nn::swkbd::TextCheckCallback callback) {
    nn::swkbd::SetTextCheckCallback(&m_keyboardArg, callback);
}

bool SoftwareKeyboard::showKeyboard() {
    std::array<float, 2> volumeBalance;
    nn::oe::GetExpectedVolumeBalance(&volumeBalance[0], &volumeBalance[1]);
    nn::oe::SetExpectedVolumeBalance(1.0f, 1.0f);

    nn::oe::SetFocusHandlingMode(nn::oe::FocusHandlingMode_SuspendHomeSleep);

    Result kbdResult = nn::swkbd::ShowKeyboard(&m_keyboardOutput, m_keyboardArg);
    static constexpr s32 s_keyboardCancelledResult = 671;
    m_cancelled = kbdResult == s_keyboardCancelledResult;

    nn::oe::SetFocusHandlingMode(nn::oe::FocusHandlingMode_AlwaysSuspend);
    nn::oe::SetExpectedVolumeBalance(volumeBalance[0], volumeBalance[1]);

    return kbdResult == 0;
}

void SoftwareKeyboard::initializeKeyboard() {
    nn::swkbd::InitializeKeyboardConfig(&m_keyboardArg.Config);
    nn::swkbd::MakePreset(&m_keyboardArg.Config, nn::swkbd::Preset_Default);

    initializeTextCheckBuffer();
    initializeWorkBuffer();
    initializeStringBuffer();
}

void SoftwareKeyboard::initializeTextCheckBuffer() {
    size_t textCheckWorkBufferSize = nn::swkbd::GetRequiredTextCheckWorkBufferSize();
    m_keyboardArg.TextCheckWorkBufferSize = textCheckWorkBufferSize;
    m_keyboardArg.TextCheckWorkBuffer = ALLOCATE(textCheckWorkBufferSize);
}

void SoftwareKeyboard::initializeWorkBuffer() {
    size_t workBufferSize = nn::swkbd::GetRequiredWorkBufferSize(false);
    m_keyboardArg.WorkBufferSize = workBufferSize;
    m_keyboardArg.WorkBuffer = ALLOCATE(workBufferSize);
}

void SoftwareKeyboard::initializeStringBuffer() {
    size_t stringBufferSize = nn::swkbd::GetRequiredStringBufferSize();
    m_keyboardOutput.BufferSize = stringBufferSize;
    m_keyboardOutput.Buffer = ALLOCATE(stringBufferSize);
}