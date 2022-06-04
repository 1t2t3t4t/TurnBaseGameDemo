// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "TurnBaseDemo/Component/LerpTransitionComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	LerpTransitionComponent = CreateDefaultSubobject<ULerpTransitionComponent>(TEXT("Lerp Transition"));
}

void ABaseCharacter::LoadCharacter(UCharacterData* CharacterData)
{
	const auto SkeletalMesh = CharacterData->SkeletalMesh.LoadSynchronous();
	const auto AnimBP = CharacterData->AnimBlueprintClass.LoadSynchronous();
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(AnimBP);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

