// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainSwitch.h"
#include "TrainIgnition.h"
#include "TrainController.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"

ATrainSwitch::ATrainSwitch()
{
}

void ATrainSwitch::BeginPlay()
{
	Super::BeginPlay();
}

void ATrainSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TrainController)
	{
		TrainController->bGo = IsOn;
	}

	FRotator TargetRotation = IsOn ? OnRotation : OffRotation;

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, Speed);

	SetActorRotation(NewRotation);
	
	
}

void ATrainSwitch::Action()
{
	IsOn = !IsOn;
	
	Switched();
}
