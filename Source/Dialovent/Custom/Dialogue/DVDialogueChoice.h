// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DVDialogueChoice.generated.h"

class UDVDialogueNode;

// Player-selected response within a dialogue
// Contains also the Dialogue Node it would lead to and any gameplay events it might triggers

USTRUCT(BlueprintType)
struct FDVDialogueChoiceData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	FText ChoiceText = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	TObjectPtr<UDVDialogueNode> NextDialogue = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	FGameplayTagContainer EventsToTrigger;

};

UCLASS()
class DIALOVENT_API UDVDialogueChoice : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	FDVDialogueChoiceData ChoiceData = FDVDialogueChoiceData();
};
