// Fill out your copyright notice in the Description page of Project Settings.


#include "Custom/Interaction/DVInteractionComponent.h"


void UDVInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UDVInteractionComponent::Interact()
{
	OnInteractStart.Broadcast();

	// Turn off the highlighting
	UpdateInteract(false);
}

void UDVInteractionComponent::CancelInteract()
{
	OnInteractCancel.Broadcast();
}

void UDVInteractionComponent::FinishInteract()
{
	// finished successfuly
	OnInteractFinish.Broadcast();
}

void UDVInteractionComponent::UpdateInteract(bool bIsInRange, UDVPlayerInteractionComponent* PlayerInteraction)
{
	OnInteractInRange.Broadcast(bIsInRange, PlayerInteraction);
}
