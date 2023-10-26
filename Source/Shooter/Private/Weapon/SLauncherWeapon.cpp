// Shooter Game. All Rights Reserved.


#include "Weapon/SLauncherWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/SProjectile.h"

void ASLauncherWeapon::StartFire()
{
    MakeShot();

    
}

void ASLauncherWeapon::MakeShot()
{
    if (!GetWorld())
    {
        StopFire();
        return;
    }

    if (IsAmmoEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
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

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ASProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
    SpawnMuzzleFX();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
