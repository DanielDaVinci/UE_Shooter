// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SBasePickup.h"
#include "SHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASHealthPickup : public ASBasePickup
{
	GENERATED_BODY()

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0.0"))
    float HealthAmount = 50.0f;
    
private:

    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
