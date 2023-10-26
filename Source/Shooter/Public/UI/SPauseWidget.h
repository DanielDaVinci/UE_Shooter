// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "SPauseWidget.generated.h"


class UButton;

UCLASS()
class SHOOTER_API USPauseWidget : public USBaseWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

private:
    UFUNCTION()
    void OnClearPause();
};
