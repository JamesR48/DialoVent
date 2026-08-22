// Fill out your copyright notice in the Description page of Project Settings.


#include "Custom/Event/DVEventSubsystem.h"

void UDVEventSubsystem::TriggerEvents(const FGameplayTagContainer& Events)
{
    if (Events.IsEmpty())
    {
        return;
    }

    OnEventsTriggered.Broadcast(Events);
}
