// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectionWidget.generated.h"

class UCharacterData;
class UButton;
class UGridPanel;

enum class ESelectionType : uint8
{
	Player,
	Enemy
};

UCLASS(Abstract)
class TURNBASEDEMO_API UCharacterSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<UCharacterData*> CharacterSelections;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UGridPanel* PlayerCharactersPanel;

	virtual void NativeConstruct() override;
	
private:
	TArray<UButton*> CreateCharacterButtons(const ESelectionType Type) const;
};
