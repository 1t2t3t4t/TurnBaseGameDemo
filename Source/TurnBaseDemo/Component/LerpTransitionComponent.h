// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LerpTransitionComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FTransitionCompletion, bool);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TURNBASEDEMO_API ULerpTransitionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition;

	UPROPERTY(VisibleAnywhere)
	FVector StartPosition;

	UPROPERTY(VisibleAnywhere)
	float Progress = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float TransitionSpeed = 1;

	bool bTransitioning = false;

	bool bFirstRound = true;
	
public:
	FTransitionCompletion OnCompleteTransition;
	
	// Sets default values for this component's properties
	ULerpTransitionComponent();

	void SetTargetPosition(const FVector Position)
	{
		TargetPosition = Position;
	}

	void SetStartTransition()
	{
		StartPosition = GetOwner()->GetActorLocation();
		bTransitioning = true;
	}

	void TransitionBack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
