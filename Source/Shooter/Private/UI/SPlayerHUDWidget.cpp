// Shooter Game. All Rights Reserved.


#include "UI/SPlayerHUDWidget.h"
#include "Components/SHealthComponent.h"
#include "Components/SWeaponComponent.h"
#include "Components/SHealthComponent.h"
#include "SUtils.h"
#include "Components/ProgressBar.h"

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

int32 USPlayerHUDWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller)
        return 0;

    const auto PlayerState = Cast<ASPlayerState>(Controller->PlayerState);

    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    FString BulletsStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletsStr.Len();

    if (SymbolsNumToAdd > 0)
    {
        BulletsStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletsStr);
    }

    return BulletsStr;
}

void USPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void USPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();

        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }
    
    UpdateHealthBar();
}

void USPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(NewPawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}

void USPlayerHUDWidget::UpdateHealthBar()
{
    if (!HealthProgressBar)
        return;

    HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
}
