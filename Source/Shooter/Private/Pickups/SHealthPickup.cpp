// Shooter Game. All Rights Reserved.


#include "Pickups/SHealthPickup.h"
#include "Components/SHealthComponent.h"
#include "SUtils.h"

bool ASHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    USHealthComponent* HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(PlayerPawn);
    if (!HealthComponent)
        return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}
