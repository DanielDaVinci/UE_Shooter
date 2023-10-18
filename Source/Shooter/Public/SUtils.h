#pragma once

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
    
};
