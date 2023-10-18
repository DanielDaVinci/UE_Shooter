// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
    
public:

    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
