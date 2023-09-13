// Shooter Game. All Rights Reserved.

#include "Components/SWeaponComponent.h"
#include "Weapon/SBaseWeapon.h"
#include "GameFramework/Character.h"

USWeaponComponent::USWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USWeaponComponent::StartFire()
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StartFire();
}

void USWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StopFire();
}

void USWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}

void USWeaponComponent::SpawnWeapon()
{
    if (!GetWorld())
        return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    CurrentWeapon = GetWorld()->SpawnActor<ASBaseWeapon>(WeaponClass);
    if (!CurrentWeapon)
        return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character);
}
