// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "SCoreTypes.h"
#include "SGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTER_API USGameOverWidget : public USBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

private:
    void OnMatchStateChanged(ESMatchState State);
    void UpdatePlayersStat();

    UFUNCTION()
    void OnResetLevel();
};
