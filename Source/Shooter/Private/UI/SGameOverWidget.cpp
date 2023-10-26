// Shooter Game. All Rights Reserved.


#include "UI/SGameOverWidget.h"

#include "SGameModeBase.h"
#include "SPlayerState.h"
#include "SPlayerStatRowWidget.h"
#include "SUtils.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void USGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<ASGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USGameOverWidget::OnResetLevel);
    }
}

void USGameOverWidget::OnMatchStateChanged(ESMatchState State)
{
    if (State == ESMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void USGameOverWidget::UpdatePlayersStat()
{
    if (!GetWorld() || !PlayerStatBox)
        return;

    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ASPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        const auto PlayerStateRowWidget = CreateWidget<USPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStateRowWidget)
             continue;

        PlayerStateRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStateRowWidget->SetKills(SUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStateRowWidget->SetDeaths(SUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStateRowWidget->SetTeam(SUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStateRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStateRowWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStateRowWidget);
    }
}

void USGameOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
