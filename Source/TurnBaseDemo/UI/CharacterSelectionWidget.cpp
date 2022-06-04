// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectionWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
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

TArray<UButton*> UCharacterSelectionWidget::CreateCharacterButtons(const ESelectionType Type) const
{
	TArray<UButton*> Result;
	for (const auto Character : CharacterSelections)
	{
		auto Button = WidgetTree->ConstructWidget<UButton>();
		const auto Text = WidgetTree->ConstructWidget<UTextBlock>();
		Text->SetText(Character->Name);
		Button->SetContent(Text);
		Result.Add(Button);
	}

	return Result;
}
