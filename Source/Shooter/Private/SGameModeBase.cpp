// Shooter Game. All Rights Reserved.


#include "SGameModeBase.h"

#include "AIController.h"
#include "Player/SBaseCharacter.h"
#include "Player/SPlayerController.h"
#include "Player/SPlayerState.h"
#include "UI/SGameHUD.h"
#include "AIController.h"
#include "SRespawnComponent.h"
#include "SUtils.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogSGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

ASGameModeBase::ASGameModeBase()
{
    DefaultPawnClass = ASBaseCharacter::StaticClass();
    PlayerControllerClass = ASPlayerController::StaticClass();
    HUDClass = ASGameHUD::StaticClass();
    PlayerStateClass = ASPlayerState::StaticClass();
}

void ASGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();

    SetMatchState(ESMatchState::InProgress);
}

UClass* ASGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<ASPlayerState>(KillerController->PlayerState) : nullptr;
    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }

    const auto VictimPlayerState = KillerController ? Cast<ASPlayerState>(VictimController->PlayerState) : nullptr;
    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void ASGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

bool ASGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        SetMatchState(ESMatchState::Pause);
    }
    
    return Super::SetPause(PC, CanUnpauseDelegate);
}

bool ASGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();

    if (PauseCleared)
    {
        SetMatchState(ESMatchState::InProgress);
    }

    return PauseCleared;
}

void ASGameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto SAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(SAIController);
    }
}

void ASGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogSGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void ASGameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }

    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ASPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }

    return GameData.DefaultTeamColor;
}

void ASGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller)
        return;

    const auto Character = Cast<ASBaseCharacter>(Controller->GetCharacter());
    if (!Character)
        return;

    const auto PlayerState = Cast<ASPlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASGameModeBase::LogPlayerInfo()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ASPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->LogInfo();
    }
}

void ASGameModeBase::StartRespawn(AController* Controller)
{
    const bool RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvailable)
        return;

    const auto RespawnComponent = SUtils::GetSPlayerComponent<USRespawnComponent>(Controller);
    if (!RespawnComponent)
        return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASGameModeBase::GameOver()
{
    UE_LOG(LogSGameModeBase, Display, TEXT("-------- GEME OVER ---------"));
    LogPlayerInfo();

    for (auto Pawn: TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }

    SetMatchState(ESMatchState::GameOver);
}

void ASGameModeBase::SetMatchState(ESMatchState State)
{
    if (MatchState == State)
        return;

    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}
