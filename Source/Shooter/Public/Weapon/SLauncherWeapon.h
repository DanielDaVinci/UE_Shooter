// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SLauncherWeapon.generated.h"

class ASProjectile;
class USoundCue;

UCLASS()
class SHOOTER_API ASLauncherWeapon : public ASBaseWeapon
{
	GENERATED_BODY()

public:

    virtual void StartFire() override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;
    
    virtual void MakeShot() override;
    
};
