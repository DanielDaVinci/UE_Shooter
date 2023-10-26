// Shooter Game. All Rights Reserved.


#include "UI/SBaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USBaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}
