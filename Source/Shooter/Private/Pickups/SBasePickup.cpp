// Shooter Game. All Rights Reserved.


#include "Pickups/SBasePickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASBasePickup::ASBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    SetRootComponent(CollisionComponent);

}

void ASBasePickup::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);

    GenerateRotationYaw();
}

void ASBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

void ASBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw * RotationSpeed * DeltaTime, 0.0f));
}

bool ASBasePickup::CouldBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool ASBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASBasePickup::Respawn, RespawnTime);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
}

void ASBasePickup::Respawn()
{
    GenerateRotationYaw();

    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void ASBasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
