// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPauseWidget.generated.h"


class UButton;

UCLASS()
class SHOOTER_API USPauseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

private:
    UFUNCTION()
    void OnClearPause();
};
