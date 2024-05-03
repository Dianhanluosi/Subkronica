// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorClick.h"
#include "Elevator.h"

AElevatorClick::AElevatorClick()
{
}

void AElevatorClick::BeginPlay()
{
	Super::BeginPlay();
}

void AElevatorClick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElevatorClick::Action()
{
	UE_LOG(LogTemp, Warning, TEXT("Action"));
	if (ER)
	{
		ER->AddTargetPosition(ClickPosition);
	}
}
