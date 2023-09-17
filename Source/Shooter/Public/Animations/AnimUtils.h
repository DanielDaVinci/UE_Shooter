#pragma once

class AnimUtils
{
public:

    template<typename T>
    static T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation)
            return nullptr;

        const TArray<FAnimNotifyEvent> NotifyEvents = Animation->Notifies;
        for (FAnimNotifyEvent NotifyEvent : NotifyEvents)
        {
            T* AnimNotify = Cast<T>(NotifyEvent.Notify);
            if (AnimNotify)
            {
                return AnimNotify;
            }
        }

        return nullptr;
    }
    
};
