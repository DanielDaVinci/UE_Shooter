// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

class USAIPerceptionComponent;
class USRespawnComponent;

UCLASS()
class SHOOTER_API ASAIController : public AAIController
{
	GENERATED_BODY()

public:

    ASAIController();
    
protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USAIPerceptionComponent* SAIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USRespawnComponent* RespawnComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";
    
    virtual void OnPossess(APawn* InPawn) override;

    virtual void Tick(float DeltaSeconds) override;

private:

    AActor* GetFocusOnActor() const;
};
