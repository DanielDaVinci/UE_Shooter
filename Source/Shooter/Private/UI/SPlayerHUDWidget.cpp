// Shooter Game. All Rights Reserved.


#include "UI/SPlayerHUDWidget.h"
#include "Components/SHealthComponent.h"
#include "Components/SWeaponComponent.h"
#include "Components/SHealthComponent.h"
#include "SUtils.h"

float USPlayerHUDWidget::GetHealthPercent() const
{
    const USHealthComponent* HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent)
        return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const USWeaponComponent* WeaponComponent = SUtils::GetSPlayerComponent<USWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}


bool USPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    const USWeaponComponent* WeaponComponent =  SUtils::GetSPlayerComponent<USWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USPlayerHUDWidget::IsPlayerAlive() const
{
    const USHealthComponent* HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(GetOwningPlayerPawn());

    return HealthComponent && !HealthComponent->IsDead();
}

bool USPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}
