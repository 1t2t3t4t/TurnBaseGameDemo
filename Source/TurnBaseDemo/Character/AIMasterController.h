// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterController.h"
#include "UObject/Object.h"
#include "AIMasterController.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDEMO_API UAIMasterController : public UObject, public IMasterController
{
	GENERATED_BODY()

public:
	virtual void EnterTurn(ABaseCharacter* Character) override;
};
