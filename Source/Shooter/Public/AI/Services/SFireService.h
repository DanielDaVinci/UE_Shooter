// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SFireService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USFireService : public UBTService
{
	GENERATED_BODY()

public:

    USFireService();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
