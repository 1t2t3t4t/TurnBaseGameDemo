// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectionWidget.generated.h"

class UCharacterData;
class UCharacterSelectionButton;
class UGridPanel;
class UHorizontalBox;

UENUM()
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
	TArray<UCharacterSelectionButton*> UserButtons;

	UPROPERTY(VisibleAnywhere)
	TArray<UCharacterSelectionButton*> EnemyButtons;

	virtual void NativeConstruct() override;
	void OnLoadedCharacterAssets();

	UFUNCTION(BlueprintCallable)
	void OnStartPlayTapped();

private:
	UPROPERTY()
	TMap<ESelectionType, UCharacterData*> Selections;
	
	TArray<UCharacterSelectionButton*> CreateCharacterButtons(const ESelectionType Type);

	UFUNCTION()
	void OnCharacterSelectionTapped(UCharacterSelectionButton* Button);
};
