// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurnBaseDemoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDEMO_API ATurnBaseDemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> PlayerPositions;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> EnemyPositions;

	virtual void BeginPlay() override;

	static AActor* GetEmptyOwnerActor(TArray<AActor*> Actors);

	AActor* GetEmptyPlayerLocation() const
	{
		return GetEmptyOwnerActor(PlayerPositions);
	}

	AActor* GetEmptyEnemyLocation() const
	{
		return GetEmptyOwnerActor(EnemyPositions);
	}
};
