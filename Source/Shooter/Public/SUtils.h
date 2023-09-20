#pragma once

class SUtils
{
public:

    template<typename T>
    static T* GetSPlayerComponent(APawn* PlayerPawn)
    {
        if (!PlayerPawn)
            return nullptr;

        UActorComponent* Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component); 
    }
    
};
