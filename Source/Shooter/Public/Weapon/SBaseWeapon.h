// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseWeapon.generated.h"

UCLASS()
class SHOOTER_API ASBaseWeapon : public AActor
{
    GENERATED_BODY()
	
public:	

	ASBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageAmount = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimerBetweenShots = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BulletSpread = 1.5f;
    
	virtual void BeginPlay() override;

    void MakeShot();
    
    APlayerController* GetPlayerController() const;
    
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    void MakeDamage(const FHitResult& HitResult);

private:

    FTimerHandle ShotTimerHandle;
    
};
