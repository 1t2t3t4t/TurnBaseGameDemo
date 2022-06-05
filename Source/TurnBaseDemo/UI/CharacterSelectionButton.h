// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSelectionWidget.h"
#include "Components/Button.h"
#include "CharacterSelectionButton.generated.h"

class UCharacterData;

UCLASS()
class TURNBASEDEMO_API UCharacterSelectionButton : public UButton
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, UCharacterSelectionButton*, Button);
	
public:
	UCharacterSelectionButton();

	UPROPERTY(VisibleAnywhere)
	UCharacterData* Data;

	ESelectionType SelectionType;
	
	FOnCharacterSelected OnCharacterSelected;

private:
	UFUNCTION()
	void OnButtonClicked();
};
