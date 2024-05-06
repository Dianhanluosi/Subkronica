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
}

void ATrainSwitch::Action()
{
	Switched();
}
