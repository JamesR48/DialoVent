// Fill out your copyright notice in the Description page of Project Settings.


#include "Custom/Dialogue/DVDialogueComponent.h"
#include "Custom/Dialogue/DVDialogueNode.h"
#include "Custom/Dialogue/DVDialogueSubsystem.h"


UDVDialogueComponent::UDVDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDVDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UDVDialogueComponent::TryStartDialogue()
{
	if (!InitialDialogueNode)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			if (UDVDialogueSubsystem* DialogueSubSystem = GameInstance->GetSubsystem<UDVDialogueSubsystem>())
			{
				DialogueSubSystem->StartDialogue(InitialDialogueNode);
			}
		}
	}
}

