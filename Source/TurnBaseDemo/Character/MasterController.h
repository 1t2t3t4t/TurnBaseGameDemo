// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MasterController.generated.h"

class ABaseCharacter;

UINTERFACE()
class UMasterController : public UInterface
{
	GENERATED_BODY()
};

class TURNBASEDEMO_API IMasterController
{
	GENERATED_BODY()

public:
	virtual void EnterTurn(ABaseCharacter *Character) = 0;
};
