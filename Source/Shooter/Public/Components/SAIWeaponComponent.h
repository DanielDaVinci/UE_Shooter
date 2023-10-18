// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SWeaponComponent.h"
#include "SAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USAIWeaponComponent : public USWeaponComponent
{
	GENERATED_BODY()


public:

    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
