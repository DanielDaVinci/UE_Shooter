// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBasePickup.h"
#include "SAmmoPickup.generated.h"

class ASBaseWeapon;
/**
 * 
 */
UCLASS()
class SHOOTER_API ASAmmoPickup : public ASBasePickup
{
	GENERATED_BODY()

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ASBaseWeapon> WeaponType;
    
private:

    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
