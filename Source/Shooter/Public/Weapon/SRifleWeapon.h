// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SRifleWeapon.generated.h"

class USWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTER_API ASRifleWeapon : public ASBaseWeapon
{
	GENERATED_BODY()

public:
    ASRifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float TimerBetweenShots = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";
    
    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USWeaponFXComponent* WeaponFXComponent;
    
    virtual void BeginPlay() override;
    
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:

    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    void MakeDamage(const FHitResult& HitResult);
    
    void InitFX();
    void SetFXActive(bool IsActive);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

    AController* GetController() const;
};
