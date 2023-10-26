// Shooter Game. All Rights Reserved.


#include "Menu/UI/SLevelItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USLevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(LevelData.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(LevelData.LevelThumb);
    }
}

void USLevelItemWidget::SetSelected(bool IsSelected)
{
    if (LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}

void USLevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USLevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USLevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USLevelItemWidget::OnLevelItemUnhovered);
    }
}

void USLevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USLevelItemWidget::OnLevelItemHovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USLevelItemWidget::OnLevelItemUnhovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}
