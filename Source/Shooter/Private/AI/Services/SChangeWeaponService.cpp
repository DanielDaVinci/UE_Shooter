// Shooter Game. All Rights Reserved.


#include "AI/Services/SChangeWeaponService.h"

#include "AIController.h"
#include "SUtils.h"
#include "SWeaponComponent.h"

USChangeWeaponService::USChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = SUtils::GetSPlayerComponent<USWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
