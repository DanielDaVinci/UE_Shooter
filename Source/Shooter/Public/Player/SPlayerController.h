// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

class USRespawnComponent;

UCLASS()
class SHOOTER_API ASPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USRespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(ESMatchState State);
    void OnMuteSound();
};
