// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterData.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class TURNBASEDEMO_API ABaseCharacter : public APawn
{
	GENERATED_BODY()

	DECLARE_DELEGATE_OneParam(FOnCharacterEndTurn, ABaseCharacter*);
	
public:
	FOnCharacterEndTurn OnEndTurn;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPlayer;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;
	
private:
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly)
	class ULerpTransitionComponent* LerpTransitionComponent;

public:
	UCapsuleComponent* GetCapsuleComponent() const
	{
		return CapsuleComponent;
	}
	
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	void LoadCharacter(UCharacterData* CharacterData);
	
protected:
	virtual void BeginPlay() override;

public:
	void Transition(const FVector Target) const;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void TransitionBack() const;

	UFUNCTION(BlueprintImplementableEvent)
	void EnterTurn();

private:
	UFUNCTION()
	void OnLerpTransitionCompleted(bool bFirstRound);
};
