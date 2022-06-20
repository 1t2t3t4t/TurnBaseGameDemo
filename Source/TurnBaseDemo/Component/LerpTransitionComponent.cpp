// Fill out your copyright notice in the Description page of Project Settings.


#include "LerpTransitionComponent.h"

ULerpTransitionComponent::ULerpTransitionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULerpTransitionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULerpTransitionComponent::TransitionBack()
{
	const auto TempPos = TargetPosition;
	TargetPosition = StartPosition;
	StartPosition = TempPos;
	Progress = 0;
	bTransitioning = true;
	bFirstRound = false;
}

void ULerpTransitionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bTransitioning)
	{
		Progress = FMath::Clamp(Progress + (TransitionSpeed * DeltaTime), 0.0f, 1.0f);
		const auto NewLocation = FMath::Lerp(StartPosition, TargetPosition, Progress);
		GetOwner()->SetActorLocation(NewLocation);

		if (Progress == 1.0)
		{
			bTransitioning = false;
			OnCompleteTransition.Broadcast(bFirstRound);
		}
	}
}
