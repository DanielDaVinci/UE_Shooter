// Shooter Game. All Rights Reserved.


#include "Menu/SMenuPlayerController.h"

void ASMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
