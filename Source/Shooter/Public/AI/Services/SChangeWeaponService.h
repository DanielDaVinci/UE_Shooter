// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:

    USChangeWeaponService();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
