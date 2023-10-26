// Shooter Game. All Rights Reserved.


#include "Weapon/Components/SWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

USWeaponFXComponent::USWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    FImpactData ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // Niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        ImpactData.NiagaraEffect,
        Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());

    // Decal
    UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(),
        ImpactData.DecalData.Material,
        ImpactData.DecalData.Size,
        Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());

    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }

    // Sound
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}
