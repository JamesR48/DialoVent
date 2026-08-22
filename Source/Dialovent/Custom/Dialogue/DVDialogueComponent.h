// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DVDialogueComponent.generated.h"

class UDVDialogueNode;

// Attach this component to any Actor you want to display dialogues
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOVENT_API UDVDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UDVDialogueComponent();
	
	// This could be a reference to a whole Dialogue Tree/Graph in the future...for now it's just the "root" or entry point of it...
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialoVent")
	TObjectPtr<UDVDialogueNode> InitialDialogueNode = nullptr;


protected:

	virtual void BeginPlay() override;

public:	
	
	UFUNCTION(BlueprintCallable, Category = "DialoVent")
	void TryStartDialogue();

};
