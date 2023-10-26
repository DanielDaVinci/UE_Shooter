// Shooter Game. All Rights Reserved.


#include "Menu/UI/SMenuWidget.h"

#include "SGameInstance.h"
#include "SLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USMenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void USMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation != HideAnimation)
        return;

    const auto SGameInstance = GetSGameInstance();
    if (!SGameInstance)
        return;
    
    UGameplayStatics::OpenLevel(this, SGameInstance->GetStartupLevel().LevelName);
}

void USMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USMenuWidget::InitLevelItems()
{
    const auto SGameInstance = GetSGameInstance();
    if (!SGameInstance)
        return;

    checkf(SGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data nust not be empty!"));

    if (!LevelItemsBox)
        return;

    LevelItemsBox->ClearChildren();

    for (auto LevelData: SGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget)
            continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (SGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(SGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(SGameInstance->GetStartupLevel());
    }
}

void USMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto SGameInstance = GetSGameInstance();
    if (!SGameInstance)
        return;

    SGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget: LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

USGameInstance* USMenuWidget::GetSGameInstance() const
{
    if (!GetWorld())
        return nullptr;

    return GetWorld()->GetGameInstance<USGameInstance>();
}
