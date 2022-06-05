// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectionButton.h"

UCharacterSelectionButton::UCharacterSelectionButton()
{
	OnClicked.AddUniqueDynamic(this, &UCharacterSelectionButton::OnButtonClicked);
}

void UCharacterSelectionButton::OnButtonClicked()
{
	OnCharacterSelected.Broadcast(this);
}