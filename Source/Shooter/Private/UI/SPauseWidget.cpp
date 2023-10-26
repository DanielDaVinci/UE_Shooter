// Shooter Game. All Rights Reserved.


#include "UI/SPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void USPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    const auto InitStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USPauseWidget::OnClearPause);
    }
}

void USPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
