// Shooter Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; };
    int32 GetTeamID() const { return TeamID; };

    void SetTeamColor(const FLinearColor Color) { TeamColor = Color; };
    FLinearColor GetTeamColor() const { return TeamColor; };
private:

    int32 TeamID;
    FLinearColor TeamColor;
};
