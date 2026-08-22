// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DVPlayerInteractionComponent.generated.h"

class UDVInteractionComponent;
class UInputAction;

// Attach this component to player controllable Pawns that could be able to interact
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOVENT_API UDVPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UDVPlayerInteractionComponent();

	// Time in seconds to search for interactables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	float SearchTickRate = 1.0f;

	// Distance from the player
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	float MaxDistanceToSearch = 150.0f;

	// This tag is for speeding up the search for interactables...could be an interface instead?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	FName InteractableTag = FName(TEXT("DVInteractable"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialoVent")
	TObjectPtr<UInputAction> InteractInputAction = nullptr;

	// The interactable that will be highlighted but not necessarily used
	UPROPERTY(Transient)
	TWeakObjectPtr<UDVInteractionComponent> ClosestInteractive = nullptr;

	// The interactable currently in use
	UPROPERTY(Transient)
	TWeakObjectPtr<UDVInteractionComponent> CurrentInteractive = nullptr;

	UPROPERTY(Transient)
	FTimerHandle UpdateInteractionsHandle;

	UPROPERTY(Transient)
	float MaxDistanceToSearchSqr = 22500.0f;

protected:
	
	virtual void BeginPlay() override;

	// Close interactables will turn on/off their heighlight in here
	UFUNCTION()
	void UpdateInteractions();

public:	
	
	UFUNCTION(BlueprintCallable, Category = "DialoVent")
	void TryInteract();
	
	// The user manually stopped the interaction
	UFUNCTION(BlueprintCallable, Category = "DialoVent")
	void StopInteract();

	// The interaction was successfuly completed
	UFUNCTION()
	void FinishedInteract();

};
