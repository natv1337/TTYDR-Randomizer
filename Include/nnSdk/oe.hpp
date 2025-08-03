#pragma once

namespace nn::oe {

enum FocusHandlingMode {
    FocusHandlingMode_SuspendHomeSleep,
    FocusHandlingMode_NoSuspend,
    FocusHandlingMode_SuspendHomeSleepNotify,
    FocusHandlingMode_AlwaysSuspend
};

struct DisplayVersion {
    char Name[16];
};

void SetFocusHandlingMode(FocusHandlingMode);
void GetDisplayVersion(DisplayVersion* outDisplayVersion);

void GetExpectedVolumeBalance(float* outApplicationVolume, float* outSdkVolume);
void SetExpectedVolumeBalance(float applicationVolume, float sdkVolume);

}