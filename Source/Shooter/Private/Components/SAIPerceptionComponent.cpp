// Shooter Game. All Rights Reserved.


#include "Components/SAIPerceptionComponent.h"
#include "AIController.h"
#include "SUtils.h"
#include "Components/SHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
        return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
        return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float ClosestDistance = MAX_FLT;
    AActor* ClosestPawn = nullptr;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = SUtils::GetSPlayerComponent<USHealthComponent>(PercieveActor);
        if (HealthComponent && !HealthComponent->IsDead()) // TODO: check if enemies or not
        {
            const float CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < ClosestDistance)
            {
                ClosestDistance = CurrentDistance;
                ClosestPawn = PercieveActor;
            }
        }
    }

    return ClosestPawn;
}
