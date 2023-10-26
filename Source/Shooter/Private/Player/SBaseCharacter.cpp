// Shooter Game. All Rights Reserved.

#include "Player/SBaseCharacter.h"
#include "Components/InputComponent.h"
#include "Components/SCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SHealthComponent.h"
#include "Components/SWeaponComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

ASBaseCharacter::ASBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

    PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<USHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<USWeaponComponent>("WeaponComponent");
}

void ASBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASBaseCharacter::OnHealthChanged);
    HealthComponent->OnDeath.AddUObject(this, &ASBaseCharacter::OnDeath);

    LandedDelegate.AddDynamic(this, &ASBaseCharacter::OnGroundLanded);
}

void ASBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

bool ASBaseCharacter::IsRunning() const
{
    return false;
}

float ASBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;

    const FVector VelocityNormal = GetVelocity().GetSafeNormal();
    const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

    return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void ASBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst)
        return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

void ASBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
    
}

void ASBaseCharacter::OnDeath()
{
    UE_LOG(LogTemp, Display, TEXT("Died"));

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

    WeaponComponent->StopFire();

    // Use animmontage or physics mesh fall
    //PlayAnimMontage(DeathAnimMontage);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void ASBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const float FallVelocityZ = -1 * GetVelocity().Z;

    if (FallVelocityZ < LandedDamageVelocity.X)
        return;

    const float FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}
