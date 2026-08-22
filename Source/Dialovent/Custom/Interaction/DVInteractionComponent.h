// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DVInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractRangeEvent, bool, bInRange, UDVPlayerInteractionComponent*, PlayerInteraction);

class UDVPlayerInteractionComponent;
class UInputAction;

// Attach this component to Actors you want to be interactive. NOTE: should add a "DVInteractable" tag to its ActorTag's too!
UCLASS()
class DIALOVENT_API UDVInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialoVent")
	FText InteractionPrompt = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialoVent")
	TObjectPtr<UInputAction> InteractInputAction = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnInteractEvent OnInteractStart;

	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnInteractEvent OnInteractCancel;

	// Event raised when the interactions completes successfuly
	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnInteractEvent OnInteractFinish;

	// Event raised when a player capable of interacting is near
	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnInteractRangeEvent OnInteractInRange;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "DialoVent")
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "DialoVent")
	void CancelInteract();

	UFUNCTION(BlueprintCallable, Category = "DialoVent")
	void FinishInteract();
	
	// Turning on/off highlighting
	void UpdateInteract(bool bIsInRange, UDVPlayerInteractionComponent* PlayerInteraction = nullptr);

};
