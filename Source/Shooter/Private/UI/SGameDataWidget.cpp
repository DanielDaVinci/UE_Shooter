// Shooter Game. All Rights Reserved.


#include "UI/SGameDataWidget.h"

int32 USGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetSGameModeBase();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USGameDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetSGameModeBase();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetSGameModeBase();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASGameModeBase* USGameDataWidget::GetSGameModeBase() const
{
    return GetWorld() ? Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASPlayerState* USGameDataWidget::GetSPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
