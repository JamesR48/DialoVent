// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DVDialogueSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueIntEvent, int32, IntValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueNodeEvent, UDVDialogueNode*, DialogueNode);

class UDVDialogueNode;

UCLASS()
class DIALOVENT_API UDVDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	// Event raised when the player wants to enter into a dialogue
	// Listened by the Character to change Input Context (could be for custom cameras in the future...)
	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnDialogueEvent OnStartDialogue;

	// Event raised when the player is advancing the currently displayed dialogue. Listened by the UI to display the new dialogue
	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnDialogueNodeEvent OnDialogueUpdated;

	// Event raised when a dialogue finishes. Listened by the Character to change Input Context
	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnDialogueEvent OnEndDialogue;

	// Event raised when the user is navigating between choices in order to turn on/off their highlight
	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnDialogueIntEvent OnChoiceUpdated;

	UPROPERTY(BlueprintAssignable, Category = "DialoVent")
	FOnDialogueIntEvent OnChoiceSelected;

	UPROPERTY(Transient)
	TObjectPtr<UDVDialogueNode> CurrentDialogue = nullptr;

	UPROPERTY(Transient)
	int32 CurrentChoiceIndex = 0;

public:

	void StartDialogue(UDVDialogueNode* InNode);
	void AdvanceDialogue();
	void EndDialogue();

	// Navigating between choices for now. Could be used to navigate/scroll up-down a long text too... 
	void DialogueMoveUp();
	void DialogueMoveDown();
};
