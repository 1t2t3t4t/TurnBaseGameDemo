// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectionWidget.h"

#include "CharacterSelectionButton.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "TurnBaseDemo/CharacterSelection.h"
#include "TurnBaseDemo/TurnBaseDemoGameInstance.h"
#include "TurnBaseDemo/Character/CharacterData.h"

void UCharacterSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> AssetIds;
	AssetManager.GetPrimaryAssetIdList(UCharacterData::AssetType, AssetIds);

	const auto Delegate = FStreamableDelegate::CreateUObject(this, &UCharacterSelectionWidget::OnLoadedCharacterAssets);
	AssetManager.LoadPrimaryAssets(AssetIds, {}, Delegate);
}

void UCharacterSelectionWidget::OnLoadedCharacterAssets()
{
	TArray<UObject*> DataList;
	UAssetManager::Get().GetPrimaryAssetObjectList(UCharacterData::AssetType, DataList);
	CharacterSelections.Reset();
	for (const auto Data : DataList)
	{
		if (UCharacterData* CharacterData = Cast<UCharacterData>(Data))
		{
			CharacterSelections.Add(CharacterData);
		}
	}
	
	UserButtons = CreateCharacterButtons(ESelectionType::Player);
	for (const auto Button : UserButtons)
	{
		PlayerCharactersPanel->AddChild(Button);
	}

	EnemyButtons = CreateCharacterButtons(ESelectionType::Enemy);
	for (const auto Button : EnemyButtons)
	{
		EnemyCharactersPanel->AddChild(Button);
	}
}

void UCharacterSelectionWidget::OnStartPlayTapped()
{
	UE_LOG(LogTemp, Display, TEXT("Abt to start"));
	UCharacterSelection* Selection = NewObject<UCharacterSelection>();
	Selection->SetSelections(Selections);
	const auto GameInstance = Cast<UTurnBaseDemoGameInstance>(GetGameInstance());
	GameInstance->SetCharacterSelection(Selection);
}

TArray<UCharacterSelectionButton*> UCharacterSelectionWidget::CreateCharacterButtons(const ESelectionType Type)
{
	TArray<UCharacterSelectionButton*> Result;
	for (const auto Character : CharacterSelections)
	{
		UCharacterSelectionButton* Button = WidgetTree->ConstructWidget<UCharacterSelectionButton>();
		
		Button->Data = Character;
		Button->SelectionType = Type;
		Button->OnCharacterSelected.AddUniqueDynamic(this, &UCharacterSelectionWidget::OnCharacterSelectionTapped);

		const auto Text = WidgetTree->ConstructWidget<UTextBlock>();
		Text->SetText(Character->Name);
		Button->SetContent(Text);
		
		Result.Add(Button);
	}
	
	return Result;
}

void UCharacterSelectionWidget::OnCharacterSelectionTapped(UCharacterSelectionButton* Button)
{
	Selections.Add(Button->SelectionType, Button->Data);
}
