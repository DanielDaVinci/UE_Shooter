// Shooter Game. All Rights Reserved.

#include "Components/SHealthComponent.h"

#include "SGameModeBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShake.h"

USHealthComponent::USHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool USHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USHealthComponent::TryToAddHealth(int32 HealthAmount)
{
    if (IsDead() || IsHealthFull())
        return false;

    SetHealth(Health + HealthAmount);
    return true;
}

// Called when the game starts
void USHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);
    
    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::OnTakeAnyDamage);
    }
}

void USHealthComponent::SetHealth(float NewHealth)
{
    const float NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const float HealthDelta = NextHealth - Health;
    
    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USHealthComponent::PlayCameraShake()
{
    if (IsDead())
        return;

    const APawn* Player = Cast<APawn>(GetOwner());
    if (!Player)
        return;

    const APlayerController* Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
        return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USHealthComponent::Killed(AController* KillerController)
{
    if (!GetWorld())
        return;
    
    const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
}

void USHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    SetHealth(Health - Damage);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }

    PlayCameraShake();
}

void USHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}
