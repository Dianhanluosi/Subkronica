// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainIgnition.h"
#include "TrainController.h"
#include "TrainSwitch.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"

ATrainIgnition::ATrainIgnition()
{
}

void ATrainIgnition::BeginPlay()
{
	Super::BeginPlay();
}

void ATrainIgnition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrainIgnition::Action()
{
	Ignition();
}
