// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SRifleWeapon.generated.h"

class USWeaponFXComponent;

/**
 * 
 */
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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

    void MakeDamage(const FHitResult& HitResult);

private:

    FTimerHandle ShotTimerHandle;
};
