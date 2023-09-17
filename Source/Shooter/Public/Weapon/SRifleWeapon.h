// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASRifleWeapon : public ASBaseWeapon
{
	GENERATED_BODY()

public:

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageAmount = 10.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimerBetweenShots = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

    void MakeDamage(const FHitResult& HitResult);

private:

    FTimerHandle ShotTimerHandle;
};
