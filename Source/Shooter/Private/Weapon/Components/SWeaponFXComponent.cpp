// Shooter Game. All Rights Reserved.


#include "Weapon/Components/SWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
USWeaponFXComponent::USWeaponFXComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void USWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    UNiagaraSystem* Effect = DefaultEffect;

    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        Effect,
        Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());
    
}
