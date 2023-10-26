// Shooter Game. All Rights Reserved.


#include "SGameInstance.h"

#include "Sound/SSoundFuncLib.h"

void USGameInstance::ToggleVolume()
{
    USSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
