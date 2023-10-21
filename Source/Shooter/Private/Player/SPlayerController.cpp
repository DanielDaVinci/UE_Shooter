// Shooter Game. All Rights Reserved.


#include "Player/SPlayerController.h"

#include "SRespawnComponent.h"

ASPlayerController::ASPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USRespawnComponent>("RespawnComponent");
}
