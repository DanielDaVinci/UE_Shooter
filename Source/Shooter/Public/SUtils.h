#pragma once

#include "Player/SPlayerState.h"

class SUtils
{
public:

    template<typename T>
    static T* GetSPlayerComponent(AActor* Player)
    {
        if (!Player)
            return nullptr;

        UActorComponent* Component = Player->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component); 
    }

    bool static AreEnemies(AController* Controller1, AController* Controller2)
    {
        if (!Controller1 || !Controller2 || Controller1 == Controller2)
            return false;

        const auto PlayerState1 = Controller1->GetPlayerState<ASPlayerState>();
        const auto PlayerState2 = Controller2->GetPlayerState<ASPlayerState>();

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }
};
