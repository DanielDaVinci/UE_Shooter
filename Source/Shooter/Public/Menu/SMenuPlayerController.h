// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASMenuPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
