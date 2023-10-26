// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SBaseCharacter.h"
#include "SAICharacter.generated.h"


class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTER_API ASAICharacter : public ASBaseCharacter
{
    GENERATED_BODY()

public:
    ASAICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* UBehaviorTreeAsset;

    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 1000.0f;

    virtual void BeginPlay() override;

    virtual void OnDeath() override;

    virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
    void UpdateHealthWidgetVisibility();
};
