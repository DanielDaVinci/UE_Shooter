// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SBaseWidget.h"
#include "SCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "SMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USGameInstance;
class USLevelItemWidget;
class USoundCue;

UCLASS()
class SHOOTER_API USMenuWidget : public USBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    UPROPERTY()
    TArray<USLevelItemWidget*> LevelItemWidgets; 
    
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    USGameInstance* GetSGameInstance() const;
};
