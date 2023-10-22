// Shooter Game. All Rights Reserved.


#include "UI/SPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool USPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USPauseWidget::OnClearPause);
    }

    return InitStatus;
}

void USPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
