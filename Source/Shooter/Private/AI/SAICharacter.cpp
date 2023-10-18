// Shooter Game. All Rights Reserved.


#include "AI/SAICharacter.h"
#include "AI/SAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SAIWeaponComponent.h"
#include "BrainComponent.h"

ASAICharacter::ASAICharacter(const FObjectInitializer& ObjInit)
    : Super::ASBaseCharacter(ObjInit.SetDefaultSubobjectClass<USAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0);
    }
}

void ASAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto SController = Cast<AAIController>(Controller);
    if (SController && SController->BrainComponent)
    {
        SController->BrainComponent->Cleanup();
    }
}
