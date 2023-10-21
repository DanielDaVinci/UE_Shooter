// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSpectatorWidget.generated.h"


UCLASS()
class SHOOTER_API USSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& CountDownTime) const;
};
