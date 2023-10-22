// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SCoreTypes.h"
#include "GameFramework/HUD.h"
#include "SGameHUD.generated.h"

UCLASS()
class SHOOTER_API ASGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;
    
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESMatchState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;
    
    void DrawCrossHair();
    void OnMatchStateChanged(ESMatchState State);
};
