// Shooter Game. All Rights Reserved.


#include "Player/SPlayerController.h"

#include "SGameInstance.h"
#include "SGameModeBase.h"
#include "SRespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ASPlayerController::ASPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USRespawnComponent>("RespawnComponent");
}

void ASPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASPlayerController::OnMatchStateChanged);
        }
    }
}

void ASPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent)
        return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASPlayerController::OnPauseGame);
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASPlayerController::OnMuteSound);
    
}

void ASPlayerController::OnPauseGame()
{
    UE_LOG(LogTemp, Warning, TEXT("PAUSE"));
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASPlayerController::OnMatchStateChanged(ESMatchState State)
{
    if (State == ESMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASPlayerController::OnMuteSound()
{
    if (!GetWorld())
        return;

    const auto SGameInstance = GetWorld()->GetGameInstance<USGameInstance>();
    if (!SGameInstance)
        return;

    SGameInstance->ToggleVolume();
}
