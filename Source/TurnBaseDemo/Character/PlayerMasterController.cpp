// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMasterController.h"

#include "BaseCharacter.h"

void UPlayerMasterController::EnterTurn(ABaseCharacter *Character)
{
	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &UPlayerMasterController::EndTurnTimer, Character);
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 5.f, false);
}

void UPlayerMasterController::EndTurnTimer(ABaseCharacter *Character)
{
	Character->EndTurn();
}
