// Fill out your copyright notice in the Description page of Project Settings.

#include "Custom/Interaction/DVPlayerInteractionComponent.h"
#include "Custom/Interaction/DVInteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UDVPlayerInteractionComponent::UDVPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDVPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// This will only be relevant for each local player!
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter || !OwnerCharacter->IsLocallyControlled())
	{
		return;
	}

	// This could be optional, the input could still live entirely within the Character/Controller if wanted
	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(OwnerCharacter->InputComponent);
	if (EIComp && InteractInputAction)
	{
		EIComp->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &UDVPlayerInteractionComponent::TryInteract);
	}

	// custom low-frequency tick for searching near interactables
	if (GetWorld())
	{
		MaxDistanceToSearchSqr = MaxDistanceToSearch * MaxDistanceToSearch;
		GetWorld()->GetTimerManager().SetTimer(UpdateInteractionsHandle, this, &UDVPlayerInteractionComponent::UpdateInteractions, SearchTickRate, true);
		UpdateInteractions();
	}
}

void UDVPlayerInteractionComponent::UpdateInteractions()
{
	AActor* Owner = GetOwner();
	if (!Owner || InteractableTag.IsNone())
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), InteractableTag, FoundActors);

	const int32 NumInteractives = FoundActors.Num();
	if ((NumInteractives <= 0) || CurrentInteractive.IsValid())
	{
		return;
	}

	// TO DO: Should be checking the dot product too! float FacingDot = ...
	float NearestDistSqr = UE_BIG_NUMBER;
	for (int idx = 0; idx < NumInteractives; idx++)
	{
		if (IsValid(FoundActors[idx]))
		{
			if (UDVInteractionComponent* Interactive = FoundActors[idx]->FindComponentByClass<UDVInteractionComponent>())
			{
				const float DistSqr = FVector::DistSquared(FoundActors[idx]->GetActorLocation(), Owner->GetActorLocation());

				if ((DistSqr < MaxDistanceToSearchSqr) && (DistSqr < NearestDistSqr))
				{
					NearestDistSqr = DistSqr;
					ClosestInteractive = Interactive;
					Interactive->UpdateInteract(true, this);
					continue;
				}

				Interactive->UpdateInteract(false);
			}
		}
	}
}

void UDVPlayerInteractionComponent::TryInteract()
{
	if (UDVInteractionComponent* Interactive = ClosestInteractive.Get())
	{
		Interactive->Interact();
		CurrentInteractive = ClosestInteractive;
		ClosestInteractive.Reset();

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(UpdateInteractionsHandle);
		}

		// Listening for when the interaction completes successfuly
		Interactive->OnInteractFinish.AddUniqueDynamic(this, &UDVPlayerInteractionComponent::FinishedInteract);
	}
}

void UDVPlayerInteractionComponent::StopInteract()
{
	if (UDVInteractionComponent* Interactive = CurrentInteractive.Get())
	{
		Interactive->CancelInteract();
	}

	FinishedInteract();
}

void UDVPlayerInteractionComponent::FinishedInteract()
{
	CurrentInteractive.Reset();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(UpdateInteractionsHandle, this, &UDVPlayerInteractionComponent::UpdateInteractions, SearchTickRate, true);
		UpdateInteractions();
	}
}

