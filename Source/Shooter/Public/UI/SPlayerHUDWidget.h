// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SCoreTypes.h"
#include "SPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USPlayerHUDWidget : public UUserWidget
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

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();
    
    virtual bool Initialize() override;

private:

    void OnHealthChanged(float Health, float HealthDelta);
};
