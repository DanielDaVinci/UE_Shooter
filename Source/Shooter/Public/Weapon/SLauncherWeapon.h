// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SLauncherWeapon.generated.h"

class ASProjectile;

UCLASS()
class SHOOTER_API ASLauncherWeapon : public ASBaseWeapon
{
	GENERATED_BODY()

public:

    virtual void StartFire() override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASProjectile> ProjectileClass;
    
    virtual void MakeShot() override;
    
};
