// Shooter Game. All Rights Reserved.


#include "AI/Services/SFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "SUtils.h"
#include "Components/SAIPerceptionComponent.h"

USFindEnemyService::USFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = SUtils::GetSPlayerComponent<USAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
