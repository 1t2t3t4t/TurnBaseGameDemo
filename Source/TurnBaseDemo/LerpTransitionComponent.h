// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LerpTransitionComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FTransitionCompletion);

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
	float TransitionSpeed = 100;

	bool bTransitioning = false;
	
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
