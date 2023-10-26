// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGameModeBase.h"
#include "SPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "SGameDataWidget.generated.h"

UCLASS()
class SHOOTER_API USGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundSecondsRemaining() const;

private:
    ASGameModeBase* GetSGameModeBase() const;
    ASPlayerState* GetSPlayerState() const;
};
