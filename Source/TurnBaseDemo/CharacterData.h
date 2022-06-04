// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TURNBASEDEMO_API UCharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category=Info)
	FText Name;
	
	UPROPERTY(EditDefaultsOnly, Category=Mesh)
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, Category=Mesh)
	TSoftClassPtr<UAnimInstance> AnimBlueprintClass;  
};
