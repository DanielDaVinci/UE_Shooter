// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTER_API ASBasePickup : public AActor
{
    GENERATED_BODY()

public:
    ASBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float RotationSpeed = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* PickupTakenSound;

    virtual void BeginPlay() override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;

    bool CouldBeTaken() const;

private:
    float RotationYaw = 0.0f;
    FTimerHandle RespawnTimerHandle;

    virtual bool GivePickupTo(APawn* PlayerPawn);
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();

};
