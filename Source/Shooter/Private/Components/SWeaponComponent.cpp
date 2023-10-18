// Shooter Game. All Rights Reserved.

#include "Components/SWeaponComponent.h"
#include "Weapon/SBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SEquipFinishedAnimNotify.h"
#include "Animations/SReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

USWeaponComponent::USWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USWeaponComponent::StartFire()
{
    if (!CanFire())
        return;

    CurrentWeapon->StartFire();
}

void USWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StopFire();
}

void USWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USWeaponComponent::Reload()
{
    ChangeClip();
}

bool USWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool USWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}

bool USWeaponComponent::TryToAddAmmo(TSubclassOf<ASBaseWeapon> WeaponType, int32 ClipsAmount)
{
    for (ASBaseWeapon* Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }

    return false;
}

bool USWeaponComponent::NeedAmmo(TSubclassOf<ASBaseWeapon> WeaponType)
{
    for (ASBaseWeapon* Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return !Weapon->IsAmmoFull();
        }
    }

    return false;
}

void USWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (ASBaseWeapon* Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void USWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    for (FWeaponData OneWeaponData : WeaponData)
    {
        ASBaseWeapon* Weapon = GetWorld()->SpawnActor<ASBaseWeapon>(OneWeaponData.WeaponClasses);
        if (!Weapon)
            continue;

        Weapon->OnClipEmpty.AddUObject(this, &USWeaponComponent::OnClipEmpty);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USWeaponComponent::AttachWeaponToSocket(ASBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent)
        return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
        return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate(
        [&](const FWeaponData& Data)
        {
            return Data.WeaponClasses == CurrentWeapon->GetClass();
        });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    Character->PlayAnimMontage(Animation);
}

void USWeaponComponent::InitAnimations()
{
    USEquipFinishedAnimNotify* EquipFinishedNotify = AnimUtils::FindNotifyByClass<USEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &USWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
        checkNoEntry();
    }

    for (FWeaponData OneWeaponData : WeaponData)
    {
        USReloadFinishedAnimNotify* ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
            checkNoEntry();

            continue;
        }

        ReloadFinishedNotify->OnNotified.AddUObject(this, &USWeaponComponent::OnReloadFinished);
    }
}

void USWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
        return;

    EquipAnimInProgress = false;
}

void USWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
        return;

    ReloadAnimInProgress = false;
}

bool USWeaponComponent::CanFire() const
{
    return CurrentWeapon
    && !EquipAnimInProgress
    && !ReloadAnimInProgress;
}

bool USWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USWeaponComponent::CanReload() const
{
    return CurrentWeapon
           && !EquipAnimInProgress
           && !ReloadAnimInProgress
           && CurrentWeapon->CanReload();
}

void USWeaponComponent::OnClipEmpty(ASBaseWeapon* AmmoEmptyWeapon)
{
    if (!AmmoEmptyWeapon)
        return;
    
    if (CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for (ASBaseWeapon* Weapon : Weapons)
        {
            if (Weapon == AmmoEmptyWeapon)
            {
                Weapon->ChangeClip();
            }
        }
    }
}

void USWeaponComponent::ChangeClip()
{
    if (!CanReload())
        return;

    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();

    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}
