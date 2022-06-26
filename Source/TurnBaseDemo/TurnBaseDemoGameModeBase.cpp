// Copyright Epic Games, Inc. All Rights Reserved.


#include "TurnBaseDemoGameModeBase.h"

#include "TurnBaseDemoGameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/AIMasterController.h"
#include "Character/BaseCharacter.h"
#include "Character/PlayerMasterController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/TurnBaseView.h"

const FName GPlayer_Position = TEXT("PlayerPosition");
const FName GEnemy_Position = TEXT("EnemyPosition");

void ATurnBaseDemoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerMasterController = NewObject<UPlayerMasterController>(this);
	AIMasterController = NewObject<UAIMasterController>(this);

	Selections = GetTurnBaseGameInstance()->TakeCharacterSelection();
	if (!Selections)
	{
		const auto DefaultSelections = NewObject<UCharacterSelection>(this, DefaultSelectionsClass);
		Selections = DefaultSelections;
	}

	UGameplayStatics::GetAllActorsWithTag(this, GPlayer_Position, PlayerPositions);
	UGameplayStatics::GetAllActorsWithTag(this, GEnemy_Position, EnemyPositions);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	SpawnCharacters();
	ConstructQueue();
	SwitchTurn();
}

void ATurnBaseDemoGameModeBase::ConstructQueue()
{
	const auto MaxIdx = FMath::Max(PlayerCharacters.Num(), EnemyCharacters.Num());
	for (auto i = 0; i < MaxIdx; i++)
	{
		if (i < PlayerCharacters.Num())
		{
			CharacterQueue.Add(PlayerCharacters[i]);
		}

		if (i < EnemyCharacters.Num())
		{
			CharacterQueue.Add(EnemyCharacters[i]);
		}
	}
}


void ATurnBaseDemoGameModeBase::SpawnCharacters()
{
	if (Selections)
	{
		if (Selections->GetSelections().Contains(ESelectionType::Player))
		{
			const auto PlayerCharacter = Selections->GetSelections()[ESelectionType::Player];
			const auto PlayerLocation = GetEmptyPlayerLocation();
			const auto Cha = SpawnCharacterAt(PlayerCharacter, PlayerLocation, PlayerCharacters);
			Cha->bIsPlayer = true;
		}
		if (Selections->GetSelections().Contains(ESelectionType::Enemy))
		{
			const auto EnemyCharacter = Selections->GetSelections()[ESelectionType::Enemy];
			const auto EnemyLocation = GetEmptyEnemyLocation();
			const auto Cha = SpawnCharacterAt(EnemyCharacter, EnemyLocation, EnemyCharacters);
			Cha->bIsPlayer = false;
		}
	}
}

ABaseCharacter* ATurnBaseDemoGameModeBase::SpawnCharacterAt(UCharacterData* CharacterData, const AActor* Location,
                                                            TArray<ABaseCharacter*>& Characters)
{
	const auto PlayerActor = GetWorld()->SpawnActor<ABaseCharacter>(CharacterClass, Location->GetActorLocation(),
	                                                                Location->GetActorRotation());
	auto AdjustedLocation = Location->GetActorLocation();
	AdjustedLocation.Z += PlayerActor->GetCapsuleComponent()->Bounds.GetBox().GetSize().Z / 2;
	PlayerActor->SetActorLocation(AdjustedLocation);
	PlayerActor->LoadCharacter(CharacterData);
	Characters.Push(PlayerActor);
	return PlayerActor;
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

void ATurnBaseDemoGameModeBase::SwitchTurn()
{
	CurrentCharacter = *CharacterQueue.GetData();
	CharacterQueue.RemoveAt(0);
	CurrentCharacter->EnterTurn();
	CurrentCharacter->OnEndTurn.BindUObject(this, &ATurnBaseDemoGameModeBase::OnCharacterEndTurn);
	TArray<UUserWidget*> TurnBaseWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, TurnBaseWidgets, UTurnBaseView::StaticClass());
	CurrentController = CurrentCharacter->bIsPlayer
		                    ? static_cast<IMasterController*>(PlayerMasterController)
		                    : static_cast<IMasterController*>(AIMasterController);
	if (TurnBaseWidgets.Num() > 0)
	{
		const bool bIsEnable = CurrentCharacter->bIsPlayer;
		for (const auto Widget : TurnBaseWidgets)
		{
			Widget->SetIsEnabled(bIsEnable);
		}
	}
	CurrentController->EnterTurn(CurrentCharacter);
	CharacterQueue.Add(CurrentCharacter);
}

void ATurnBaseDemoGameModeBase::OnCharacterEndTurn(ABaseCharacter* Character)
{
	CurrentCharacter = nullptr;
	Character->OnEndTurn.Unbind();
	SwitchTurn();
}
