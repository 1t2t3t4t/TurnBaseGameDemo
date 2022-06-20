// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBaseController.h"


// Sets default values
ATurnBaseController::ATurnBaseController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurnBaseController::BeginPlay()
{
	Super::BeginPlay();
	TurnBaseView = CreateWidget<UTurnBaseView>(this, TurnBaseViewClass);
	TurnBaseView->AddToViewport();
}

// Called every frame
void ATurnBaseController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurnBaseController::PressedAction()
{
	UE_LOG(LogTemp, Warning, TEXT("TEST"));
}
