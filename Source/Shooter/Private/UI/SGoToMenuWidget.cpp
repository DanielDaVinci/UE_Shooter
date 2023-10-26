// Shooter Game. All Rights Reserved.


#include "UI/SGoToMenuWidget.h"

#include "SGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USGoToMenuWidget::OnGoToMenu);
    }
}

void USGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld())
        return;

    const auto SGameInstance = GetWorld()->GetGameInstance<USGameInstance>();
    if (!SGameInstance || SGameInstance->GetMenuLevelName().IsNone())
        return;
    
    UGameplayStatics::OpenLevel(this, SGameInstance->GetMenuLevelName());
}
