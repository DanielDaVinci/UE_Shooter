// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "SCoreTypes.h"
#include "SPlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTER_API USPlayerHUDWidget : public USBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString FormatBullets(int32 BulletsNum) const;
    
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* DamageAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category  ="UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;

    virtual void NativeOnInitialized() override;

private:
    void OnHealthChanged(float Health, float HealthDelta);
    void OnNewPawn(APawn* NewPawn);
    void UpdateHealthBar();
};
