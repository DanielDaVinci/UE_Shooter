// Shooter Game. All Rights Reserved.


#include "Menu/UI/SMenuHUD.h"

#include "SBaseWidget.h"
#include "Blueprint/UserWidget.h"

void ASMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<USBaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
