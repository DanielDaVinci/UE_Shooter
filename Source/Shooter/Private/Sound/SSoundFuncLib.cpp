// Shooter Game. All Rights Reserved.


#include "Sound/SSoundFuncLib.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSSoundFuncLib, All, All);

void USSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if (!SoundClass)
        return;

    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
    UE_LOG(LogSSoundFuncLib, Display, TEXT("Sound class volume was changed: %s = %f"), *SoundClass->GetName(),
        SoundClass->Properties.Volume);
}

void USSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if (!SoundClass)
        return;

    const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
