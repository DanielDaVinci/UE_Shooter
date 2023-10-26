// Shooter Game. All Rights Reserved.


#include "Menu/SMenuGameModeBase.h"

#include "Menu/SMenuPlayerController.h"
#include "Menu/UI/SMenuHUD.h"

ASMenuGameModeBase::ASMenuGameModeBase()
{
    PlayerControllerClass = ASMenuPlayerController::StaticClass();
    HUDClass = ASMenuHUD::StaticClass();
}
