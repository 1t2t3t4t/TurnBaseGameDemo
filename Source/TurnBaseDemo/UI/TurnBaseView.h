// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "TurnBaseView.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDEMO_API UTurnBaseView : public UUserWidget
{
	GENERATED_BODY()

private:
	void PerformAction() const;
};
