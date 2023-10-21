// Shooter Game. All Rights Reserved.


#include "Components/SRespawnComponent.h"

#include "SGameModeBase.h"

USRespawnComponent::USRespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}

void USRespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld())
        return;

    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool USRespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USRespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld())
            return;

        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
