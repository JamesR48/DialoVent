// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "DVEventSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventSysContainerEvent, const FGameplayTagContainer&, Events);

UCLASS()
class DIALOVENT_API UDVEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnEventSysContainerEvent OnEventsTriggered;

public:

	UFUNCTION(BlueprintCallable, Category = "DialoVent")
	void TriggerEvents(const FGameplayTagContainer& Events);
};
