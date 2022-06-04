// Copyright Epic Games, Inc. All Rights Reserved.


#include "TurnBaseDemoGameModeBase.h"

#include "Kismet/GameplayStatics.h"

const FName GPlayer_Position = TEXT("PlayerPosition");
const FName GEnemy_Position = TEXT("EnemyPosition");

void ATurnBaseDemoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsWithTag(this, GPlayer_Position, PlayerPositions);
	UGameplayStatics::GetAllActorsWithTag(this, GEnemy_Position, EnemyPositions);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

AActor* ATurnBaseDemoGameModeBase::GetEmptyOwnerActor(TArray<AActor*> Actors)
{
	return *Actors.FindByPredicate([](const AActor* Actor)
		{
			return Actor->GetOwner() == nullptr;
		});
}
