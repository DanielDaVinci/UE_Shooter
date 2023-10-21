// Shooter Game. All Rights Reserved.


#include "Player/SPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSPlayerState, All, All);

void ASPlayerState::LogInfo()
{
    UE_LOG(LogSPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
