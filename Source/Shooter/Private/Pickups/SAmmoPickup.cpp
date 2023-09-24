// Shooter Game. All Rights Reserved.


#include "Pickups/SAmmoPickup.h"
#include "Components/SHealthComponent.h"
#include "Components/SWeaponComponent.h"
#include "SUtils.h"

bool ASAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const USHealthComponent* HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    USWeaponComponent* WeaponComponent = SUtils::GetSPlayerComponent<USWeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return false;
    
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
