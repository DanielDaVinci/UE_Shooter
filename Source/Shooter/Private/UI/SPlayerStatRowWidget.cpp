// Shooter Game. All Rights Reserved.


#include "UI/SPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if (!PlayerNameTextBlock)
        return;

    PlayerNameTextBlock->SetText(Text);
}

void USPlayerStatRowWidget::SetKills(const FText& Text)
{
    if (!KillsTextBlock)
        return;

    KillsTextBlock->SetText(Text);
}

void USPlayerStatRowWidget::SetDeaths(const FText& Text)
{
    if (!DeathsTextBlock)
        return;

    DeathsTextBlock->SetText(Text);
}

void USPlayerStatRowWidget::SetTeam(const FText& Text)
{
    if (!TeamTextBlock)
        return;

    TeamTextBlock->SetText(Text);
}

void USPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage)
        return;

    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
    if (!TeamImage)
        return;

    TeamImage->SetColorAndOpacity(Color);
}
