// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSoundFuncLib.generated.h"

class USoundClass;

UCLASS()
class SHOOTER_API USSoundFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

    UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass* SoundClass);
};
