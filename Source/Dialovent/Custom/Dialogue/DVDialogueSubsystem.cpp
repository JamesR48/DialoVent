// Fill out your copyright notice in the Description page of Project Settings.


#include "Custom/Dialogue/DVDialogueSubsystem.h"
#include "Custom/Dialogue/DVDialogueNode.h"
#include "Custom/Dialogue/DVDialogueChoice.h"
#include "Custom/Event/DVEventSubsystem.h"


void UDVDialogueSubsystem::StartDialogue(UDVDialogueNode* InNode)
{
	if (InNode)
	{
        CurrentChoiceIndex = 0;
        CurrentDialogue = InNode;
        OnStartDialogue.Broadcast();

        // Displaying the dialogue in the UI
        OnDialogueUpdated.Broadcast(CurrentDialogue);
	}
}

void UDVDialogueSubsystem::AdvanceDialogue()
{
    if (!CurrentDialogue)
    {
        return;
    }

    // In case a Dialogue has Choices
    if ((CurrentDialogue->DialogueNode.Choices.Num() > 0) && CurrentDialogue->DialogueNode.Choices.IsValidIndex(CurrentChoiceIndex))
    {
        UDVDialogueChoice* SelectedChoice = CurrentDialogue->DialogueNode.Choices[CurrentChoiceIndex];

        if (SelectedChoice)
        {
            // Trigger any event it might have
            if (!SelectedChoice->ChoiceData.EventsToTrigger.IsEmpty())
            {
                if (UGameInstance* GameInstance = GetGameInstance())
                {
                    if (UDVEventSubsystem* EventSubSystem = GameInstance->GetSubsystem<UDVEventSubsystem>())
                    {
                        EventSubSystem->TriggerEvents(SelectedChoice->ChoiceData.EventsToTrigger);
                    }
                }
            }

            // Go to the next Dialogue (if any) 
            UDVDialogueNode* NextDialogue = SelectedChoice->ChoiceData.NextDialogue;
            if (NextDialogue)
            {
                CurrentDialogue = NextDialogue;
                OnDialogueUpdated.Broadcast(CurrentDialogue);
                CurrentChoiceIndex = 0;
                return;
            }
        }
        
        // Calling EndDialogue here will finish the whole conversation whens selecting a choice with events but with no next Dialogue
        //EndDialogue();
        return;
    }

    if (CurrentDialogue->DialogueNode.NextDialogue)
    {
        CurrentChoiceIndex = 0;
        CurrentDialogue = CurrentDialogue->DialogueNode.NextDialogue;
        OnDialogueUpdated.Broadcast(CurrentDialogue);
        return;
    }

    // Nothing else? Dialogue is over
    EndDialogue();
}

void UDVDialogueSubsystem::EndDialogue()
{
    CurrentDialogue = nullptr;
    OnEndDialogue.Broadcast();
}

void UDVDialogueSubsystem::DialogueMoveUp()
{
    if (!CurrentDialogue)
    {
        return;
    }

    const int32 NumChoices = CurrentDialogue->DialogueNode.Choices.Num();

    if (NumChoices <= 0)
    {
        return;
    }

    CurrentChoiceIndex--;

    // Avoid overflowing choices! Go to the last one
    if (CurrentChoiceIndex < 0)
    {
        CurrentChoiceIndex = NumChoices - 1;
    }

    OnChoiceUpdated.Broadcast(CurrentChoiceIndex);
}

void UDVDialogueSubsystem::DialogueMoveDown()
{
    if (!CurrentDialogue)
    {
        return;
    }

    const int32 NumChoices = CurrentDialogue->DialogueNode.Choices.Num();

    if (NumChoices <= 0)
    {
        return;
    }

    CurrentChoiceIndex++;

    // Avoid overflowing choices! Return to the first one
    if (CurrentChoiceIndex >= NumChoices)
    {
        CurrentChoiceIndex = 0;
    }

    OnChoiceUpdated.Broadcast(CurrentChoiceIndex);
}
