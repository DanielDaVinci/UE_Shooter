// Shooter Game. All Rights Reserved.


#include "UI/SSpectatorWidget.h"

#include "SRespawnComponent.h"
#include "SUtils.h"

bool USSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = SUtils::GetSPlayerComponent<USRespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
        return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
