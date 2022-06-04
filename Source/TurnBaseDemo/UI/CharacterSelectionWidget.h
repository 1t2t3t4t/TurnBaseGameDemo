// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectionWidget.generated.h"

class UCharacterData;
class UButton;
class UGridPanel;
class UHorizontalBox;

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
	UPROPERTY(VisibleAnywhere)
	TArray<UCharacterData*> CharacterSelections;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UHorizontalBox* PlayerCharactersPanel;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UHorizontalBox* EnemyCharactersPanel;

	UPROPERTY(VisibleAnywhere)
	TArray<UButton*> UserButtons;

	UPROPERTY(VisibleAnywhere)
	TArray<UButton*> EnemyButtons;

	virtual void NativeConstruct() override;
	void OnLoadedCharacterAssets();

private:
	TArray<UButton*> CreateCharacterButtons(const ESelectionType Type) const;
};
