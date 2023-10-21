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
    const USWeaponComponent* WeaponComponent = SUtils::GetSPlayerComponent<USWeaponComponent>(GetOwningPlayerPawn());
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

bool USPlayerHUDWidget::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }

    return Super::Initialize();
}

void USPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
}

void USPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(NewPawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USPlayerHUDWidget::OnHealthChanged);
    }
}
