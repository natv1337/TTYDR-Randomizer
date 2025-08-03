#include "Patches/MainInitHook.hpp"

#include "Core/Logger.hpp"
#include "SoftwareKeyboard.hpp"

#include "nnSdk/util.hpp"

#include "Util.hpp"

using namespace nn::swkbd;

TextCheckResult checkIpAddressCallback(void* outputStringBuffer, size_t* outputStringSize, String* string) {
    char utf8StringBuffer[0x80];
    nn::util::ConvertStringUtf16NativeToUtf8(
        utf8StringBuffer, 
        sizeof(utf8StringBuffer),
        reinterpret_cast<const char16_t*>(string->Buffer), 
        string->BufferSize
    );

    if (!Util::isIpv4AddressValid(reinterpret_cast<const char*>(string->Buffer))) {
        return TextCheckResult_ShowFailureDialog;
    }

    char dialogTextBuffer[0x80];
    nn::util::SNPrintf(dialogTextBuffer, sizeof(dialogTextBuffer), "Connect to %s?", string->Buffer);

    memcpy(outputStringBuffer, dialogTextBuffer, sizeof(dialogTextBuffer));
    return TextCheckResult_ShowConfirmDialog;
}

void MainInitHook::Callback() {
    Orig();

#ifdef MOD_DEBUG
    Logger& logger = Logger::getLogger();
    logger.initializeFileLogger();

    SoftwareKeyboard keyboard(EncodingMode::UTF8);
    keyboard.setHeaderText("IP Address of Logging Server");
    keyboard.setGuideText("IP Address");
    keyboard.setSubText("IP Address of Logging Server");
    keyboard.setInputTextMaxLength(15);

    if (keyboard.showKeyboard()) {
        logger.initializeFtpLogger(keyboard.getTextUtf8());
    }
#endif
}