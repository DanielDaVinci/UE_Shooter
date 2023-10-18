// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SFindEnemyService.generated.h"




UCLASS()
class SHOOTER_API USFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:

    USFindEnemyService();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
