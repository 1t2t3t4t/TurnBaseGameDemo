// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSelection.h"
#include "TurnBaseDemoGameInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "TurnBaseDemoGameModeBase.generated.h"

class UPlayerMasterController;
class UAIMasterController;
class IMasterController;

UCLASS()
class TURNBASEDEMO_API ATurnBaseDemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> PlayerPositions;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> EnemyPositions;

	UPROPERTY(VisibleAnywhere)
	UCharacterSelection* Selections;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterSelection> DefaultSelectionsClass;

	UPROPERTY(EditDefaultsOnly, Category=Template)
	TSubclassOf<ABaseCharacter> CharacterClass;

	UPROPERTY(VisibleAnywhere, Category=Gameplay)
	TArray<ABaseCharacter*> CharacterQueue;

	UPROPERTY(VisibleAnywhere, Category=Gameplay)
	ABaseCharacter* CurrentCharacter;

	UPROPERTY(VisibleAnywhere, Category=Gameplay)
	UPlayerMasterController* PlayerMasterController;

	UPROPERTY(VisibleAnywhere, Category=Gameplay)
	UAIMasterController* AIMasterController;

	IMasterController* CurrentController;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay)
	TArray<ABaseCharacter*> PlayerCharacters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Gameplay)
	TArray<ABaseCharacter*> EnemyCharacters;

	virtual void BeginPlay() override;

	static AActor* GetEmptyOwnerActor(TArray<AActor*> Actors);
	UTurnBaseDemoGameInstance* GetTurnBaseGameInstance() const;

	AActor* GetEmptyPlayerLocation() const
	{
		return GetEmptyOwnerActor(PlayerPositions);
	}

	AActor* GetEmptyEnemyLocation() const
	{
		return GetEmptyOwnerActor(EnemyPositions);
	}

private:
	void ConstructQueue();
	void SpawnCharacters();
	
	ABaseCharacter* SpawnCharacterAt(UCharacterData* CharacterData, const AActor* Location,
	                                 TArray<ABaseCharacter*>& Characters);
	void SwitchTurn();
	void OnCharacterEndTurn(ABaseCharacter* Character);
};
