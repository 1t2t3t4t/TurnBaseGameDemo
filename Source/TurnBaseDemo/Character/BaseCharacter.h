// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterData.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TURNBASEDEMO_API ABaseCharacter : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	class ULerpTransitionComponent* LerpTransitionComponent;

public:
	// Sets default values for this pawn's properties
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	void LoadCharacter(UCharacterData* CharacterData);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Transition(const FVector Target) const;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void TransitionBack() const;

private:
	UFUNCTION()
	void OnLerpTransitionCompleted(bool bFirstRound);
};
