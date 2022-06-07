// Copyright Epic Games, Inc. All Rights Reserved.


#include "TurnBaseDemoGameModeBase.h"

#include "TurnBaseDemoGameInstance.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

const FName GPlayer_Position = TEXT("PlayerPosition");
const FName GEnemy_Position = TEXT("EnemyPosition");

void ATurnBaseDemoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Selections = GetTurnBaseGameInstance()->TakeCharacterSelection();
	
	UGameplayStatics::GetAllActorsWithTag(this, GPlayer_Position, PlayerPositions);
	UGameplayStatics::GetAllActorsWithTag(this, GEnemy_Position, EnemyPositions);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	SpawnCharacters();
}

void ATurnBaseDemoGameModeBase::SpawnCharacters() const
{
	if (Selections && Selections->GetSelections().Contains(ESelectionType::Player))
	{
		const auto PlayerCharacter = Selections->GetSelections()[ESelectionType::Player];
		const auto PlayerLocation = GetEmptyPlayerLocation();
		const auto PlayerActor = GetWorld()->SpawnActor<ABaseCharacter>(PlayerLocation->GetActorLocation(), PlayerLocation->GetActorRotation());
		PlayerActor->LoadCharacter(PlayerCharacter);
	}
}

AActor* ATurnBaseDemoGameModeBase::GetEmptyOwnerActor(TArray<AActor*> Actors)
{
	return *Actors.FindByPredicate([](const AActor* Actor)
		{
			return Actor->GetOwner() == nullptr;
		});
}

UTurnBaseDemoGameInstance* ATurnBaseDemoGameModeBase::GetTurnBaseGameInstance() const
{
	return Cast<UTurnBaseDemoGameInstance>(GetGameInstance());
}