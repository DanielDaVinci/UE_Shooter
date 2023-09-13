// Shooter Game. All Rights Reserved.


#include "SGameModeBase.h"
#include "Player/SBaseCharacter.h"
#include "Player/SPlayerController.h"
#include "UI/SGameHUD.h"

ASGameModeBase::ASGameModeBase()
{
    DefaultPawnClass = ASBaseCharacter::StaticClass();
    PlayerControllerClass = ASPlayerController::StaticClass();
    HUDClass = ASGameHUD::StaticClass();
} 

