// Shooter Game. All Rights Reserved.


#include "AI/Decorators/SNeedAmmoDecorator.h"

#include "AIController.h"
#include "SUtils.h"
#include "SWeaponComponent.h"

USNeedAmmoDecorator::USNeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool USNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto WeaponComponent = SUtils::GetSPlayerComponent<USWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
