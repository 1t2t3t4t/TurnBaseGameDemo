// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterController.h"
#include "UObject/Object.h"
#include "PlayerMasterController.generated.h"

UCLASS()
class TURNBASEDEMO_API UPlayerMasterController : public UObject, public IMasterController
{
	GENERATED_BODY()

public:
	
	virtual void EnterTurn(ABaseCharacter *Character) override;

	void EndTurnTimer(ABaseCharacter *Character);
};
