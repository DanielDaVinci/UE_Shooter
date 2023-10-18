// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SNeedAmmoDecorator.generated.h"

class ASBaseWeapon;

UCLASS()
class SHOOTER_API USNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
