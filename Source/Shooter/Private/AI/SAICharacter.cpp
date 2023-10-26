// Shooter Game. All Rights Reserved.


#include "AI/SAICharacter.h"
#include "AI/SAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SAIWeaponComponent.h"
#include "BrainComponent.h"
#include "SHealthComponent.h"
#include "UI/SHealthBarWidget.h"
#include "Components/WidgetComponent.h"

ASAICharacter::ASAICharacter(const FObjectInitializer& ObjInit)
    : Super::ASBaseCharacter(ObjInit.SetDefaultSubobjectClass<USAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateHealthWidgetVisibility();
}

void ASAICharacter::UpdateHealthWidgetVisibility()
{
    if (!GetWorld() ||
        !GetWorld()->GetFirstPlayerController() ||
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
        return;

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());

    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}

void ASAICharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthWidgetComponent);
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

void ASAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<USHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget)
        return;

    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}
