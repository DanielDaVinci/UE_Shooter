// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SBaseCharacter.h"
#include "SAICharacter.generated.h"


class UBehaviorTree;

UCLASS()
class SHOOTER_API ASAICharacter : public ASBaseCharacter
{
	GENERATED_BODY()

public:

    ASAICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* UBehaviorTreeAsset;

protected:

    virtual void OnDeath() override;
    
};
