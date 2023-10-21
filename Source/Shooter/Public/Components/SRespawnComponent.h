// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRespawnComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTER_API USRespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USRespawnComponent();

    void Respawn(int32 RespawnTime);

    int32 GetRespawnCountDown() const { return RespawnCountDown; };
    bool IsRespawnInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;

    void RespawnTimerUpdate();
};
