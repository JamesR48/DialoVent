// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DVDialogueNode.generated.h"

class UDVDialogueChoice;

// A single point in a dialogue tree/graph
// Contains the speaker's text and defines the next node or available choices

USTRUCT(BlueprintType)
struct FDVDialogueNodeData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialoVent")
	FText SpeakerName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	FText DialogueText = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	TObjectPtr<UDVDialogueNode> NextDialogue = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	TArray<TObjectPtr<UDVDialogueChoice>> Choices = {};

	// TO DO: Audio track, duration, states, image (if needed), animation (if needed)...

};

UCLASS()
class DIALOVENT_API UDVDialogueNode : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DialoVent")
	FDVDialogueNodeData DialogueNode = FDVDialogueNodeData();
	
};
