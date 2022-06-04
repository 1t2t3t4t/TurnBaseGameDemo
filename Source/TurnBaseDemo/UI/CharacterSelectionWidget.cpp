// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectionWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "TurnBaseDemo/CharacterData.h"

void UCharacterSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	auto Btns = CreateCharacterButtons(ESelectionType::Player);
	for (auto b : Btns)
	{
		PlayerCharactersPanel->AddChild(b);
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
