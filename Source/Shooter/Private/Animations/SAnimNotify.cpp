// Shooter Game. All Rights Reserved.


#include "Animations/SAnimNotify.h"

void USAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}