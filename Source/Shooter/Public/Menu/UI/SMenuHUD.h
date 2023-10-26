// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    virtual void BeginPlay() override;
};
