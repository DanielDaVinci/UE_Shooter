// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBaseWidget.generated.h"

class USoundCue;

UCLASS()
class SHOOTER_API USBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void Show();
    
protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* OpenSound;
};
