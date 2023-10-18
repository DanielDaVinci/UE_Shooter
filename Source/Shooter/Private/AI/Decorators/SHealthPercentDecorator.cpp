// Shooter Game. All Rights Reserved.


#include "AI/Decorators/SHealthPercentDecorator.h"

#include "AIController.h"
#include "SHealthComponent.h"
#include "SUtils.h"

USHealthPercentDecorator::USHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead())
        return false;
    
    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
