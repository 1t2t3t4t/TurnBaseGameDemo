// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CharacterSelectionWidget.h"
#include "UObject/Object.h"
#include "CharacterSelection.generated.h"

class UCharacterData;

UCLASS(Blueprintable, BlueprintType)
class TURNBASEDEMO_API UCharacterSelection : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<ESelectionType, UCharacterData*> Selections;
	
public:
	TMap<ESelectionType, UCharacterData*> GetSelections() const
	{
		return Selections;
	}

	void SetSelections(const TMap<ESelectionType, UCharacterData*> NewSelections)
	{
		this->Selections = NewSelections;
	}
};
