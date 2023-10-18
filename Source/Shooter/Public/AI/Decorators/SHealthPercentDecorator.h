// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USHealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai")
    float HealthPercent = 0.6f;
    
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
