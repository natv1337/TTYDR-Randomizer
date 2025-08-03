#pragma once

#include <string>

#include "Types.hpp"
#include "result.hpp"

namespace nn::swkbd {

const s32 OkTextMaxLength = 8;
const s32 HeaderTextMaxLength = 64;
const int32_t SubTextMaxLength = 128;
const int32_t GuideTextMaxLength = 256;

enum KeyboardMode {
    KeyboardMode_LanguageSet1,
    KeyboardMode_Numeric,
    KeyboardMode_ASCII,
    KeyboardMode_LanguageSet1Latin,
    KeyboardMode_Alphabet,
    KeyboardMode_SimplifiedChinese,
    KeyboardMode_TraditionalChinese,
    KeyboardMode_Korean,
    KeyboardMode_LanguageSet2,
    KeybaordMode_LanguageSet2Latin,
    KeyboardMode_Max
};

enum InitialCursorPos {
    InitialCursorPos_First,
    InitialCursorPos_Last,
    InitialCursorPos_Max
};

enum PasswordMode {
    PasswordMode_Show,
    PasswordMode_Hide,
    PasswordMode_Max
};

enum InputFormMode {
    InputFormMode_OneLine,
    InputFormMode_MultiLine,
    InputFormMode_Separate,
    InputFormMode_Max
};

enum Preset {
    Preset_Default,
    Preset_Password,
    Preset_UserName,
    Preset_DownloadCode,
    Preset_Max
};

enum TextCheckResult {
    TextCheckResult_Success,
    TextCheckResult_ShowFailureDialog,
    TextCheckResult_ShowConfirmDialog,
    TextCheckResult_Max
};

struct DictionaryInfo {
    u32 Offset;
    u16 Size;
    u16 Language;
};

struct KeyboardConfig {
    KeyboardMode Mode;
    char16_t OkText[ OkTextMaxLength + 1 ];
    char16_t LeftOptionalSymbolKey;
    char16_t RightOptionalSymbolKey;
    bool IsPredictionEnabled;
    u32 InvalidCharFlag;
    InitialCursorPos InitialCursorPosition;
    char16_t HeaderText[ HeaderTextMaxLength + 1 ];
    char16_t SubText[ SubTextMaxLength + 1 ];
    char16_t GuideText[ GuideTextMaxLength + 1 ];
    s32 TextMaxLength;
    s32 TextMinLength;
    PasswordMode CurrentPasswordMode;
    InputFormMode CurrentInputFormMode;
    bool IsUseNewLine;
    bool IsUseUtf8;
    bool IsUseBlurBackground;
    s32 InitialStringOffset;
    s32 InitialStringLength;
    s32 UserDictionaryOffset;
    s32 UserDictionaryNum;
    bool IsUseTextCheck;
    void* TextCheckCallback = nullptr;
    s32 SeparateTextPos[8];
    DictionaryInfo CustomizedDicInfoList[ 24 ];
    u8 CustomizedDicCount;
    bool IsCancelButtonDisabled;
private:
    u8 Reserved[14];
};
static_assert(sizeof(KeyboardConfig) == 0x4D0);

struct ShowKeyboardArg {
    KeyboardConfig Config;
    void* WorkBuffer = nullptr;
    size_t WorkBufferSize = 0;
    void* TextCheckWorkBuffer = nullptr;
    size_t TextCheckWorkBufferSize = 0;
    const void* CustomizedDictionaryBuffer = nullptr;
    size_t CustomizedDictionaryBufferSize = 0;
};
static_assert(sizeof(ShowKeyboardArg) == 0x500);

struct String {
    void* Buffer;
    size_t BufferSize;
};

unsigned long GetRequiredWorkBufferSize(bool);
unsigned long GetRequiredStringBufferSize();
unsigned long GetRequiredTextCheckWorkBufferSize();
void MakePreset(KeyboardConfig*, Preset);
void SetHeaderText(KeyboardConfig*, const char16_t*);
void SetSubText(KeyboardConfig*, const char16_t*);
void SetOkText(KeyboardConfig*, const char16_t*);
void SetOkTextUtf8(KeyboardConfig*, const char*);
void SetLeftOptionalSymbolKey(KeyboardConfig*, char16_t);
void SetLeftOptionalSymbolKeyUtf8(KeyboardConfig*, const char*);
void SetRightOptionalSymbolKey(KeyboardConfig*, char16_t);
void SetRightOptionalSymbolKeyUtf8(KeyboardConfig*, const char*);
void SetHeaderText(KeyboardConfig*, const char16_t*);
void SetHeaderTextUtf8(KeyboardConfig*, const char*);
void SetSubText(KeyboardConfig*, const char16_t*);
void SetSubTextUtf8(KeyboardConfig*, const char*);
void SetGuideText(KeyboardConfig*, const char16_t*);
void SetGuideTextUtf8(KeyboardConfig*, const char*);
void SetInitialText(ShowKeyboardArg*, const char16_t*);
void SetInitialTextUtf8(ShowKeyboardArg*, const char*);
Result ShowKeyboard(String*, const ShowKeyboardArg&);
void InitializeKeyboardConfig(KeyboardConfig*);

typedef TextCheckResult (*TextCheckCallback)(void*, u64*, String*);
void SetTextCheckCallback(ShowKeyboardArg*, TextCheckCallback);

} // namespace nn::swkbd