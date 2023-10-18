// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:

    AActor* GetClosestEnemy() const;
	
};
