// Shooter Game. All Rights Reserved.


#include "Weapon/SRifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/SWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASRifleWeapon::ASRifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USWeaponFXComponent>("WeaponFXComponent");
}

void ASRifleWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASRifleWeapon::MakeShot, TimerBetweenShots, true);
    MakeShot();
}

void ASRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void ASRifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void ASRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }

    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
    
    DecreaseAmmo();
}

bool ASRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    const float HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    return true;
}

void ASRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;
    
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);
}

void ASRifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    if (!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    SetFXActive(true);
}

void ASRifleWeapon::SetFXActive(bool IsActive)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }

    if (FireAudioComponent)
    {
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
    }
}

void ASRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ASRifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
