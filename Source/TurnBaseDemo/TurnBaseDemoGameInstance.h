// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TurnBaseDemoGameInstance.generated.h"

UCLASS()
class TURNBASEDEMO_API UTurnBaseDemoGameInstance final : public UGameInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category="Character Selection")
	class UCharacterSelection* CharacterSelection;
	
public:
	UCharacterSelection* TakeCharacterSelection()
	{
		const auto ReturnSelection = CharacterSelection;
		CharacterSelection = nullptr;
		return ReturnSelection;
	}
	
	void SetCharacterSelection(UCharacterSelection* NewCharacterSelection)
	{
		CharacterSelection = NewCharacterSelection;
	}
};
