// Shooter Game. All Rights Reserved.


#include "AI/Services/SFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SUtils.h"
#include "Components/SWeaponComponent.h"

USFireService::USFireService()
{
    NodeName = "Fire";
}

void USFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = SUtils::GetSPlayerComponent<USWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
