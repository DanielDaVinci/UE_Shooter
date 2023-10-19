// Shooter Game. All Rights Reserved.


#include "AI/SAIController.h"
#include "AI/SAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SAIPerceptionComponent.h"

ASAIController::ASAIController()
{
    SAIPerceptionComponent = CreateDefaultSubobject<USAIPerceptionComponent>("SPerceptionComponent");
    SetPerceptionComponent(*SAIPerceptionComponent);

    bWantsPlayerState = true;
}

void ASAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ASAICharacter>(InPawn);
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->UBehaviorTreeAsset);
    }
}

void ASAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent())
        return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
