// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainIgnition.h"
#include "TrainController.h"
#include "TrainSwitch.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "KeySocket.h"
#include "PowerPlantSpinner.h"

ATrainIgnition::ATrainIgnition()
{
	PrimaryActorTick.bCanEverTick = true;

	// Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	// RootComponent = Button;
}

void ATrainIgnition::BeginPlay()
{
	Super::BeginPlay();
}

void ATrainIgnition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (Spinner)
	// {
	// 	HasPower = Spinner->IsOn;
	// }

	if (!IsPowered)
	{
		if (TrainController)
		{
			TrainController->HasPower = false;

		}
	}
}

void ATrainIgnition::Action()
{

	Pressed();
	UE_LOG(LogTemp, Warning, TEXT("Error"), IsPowered ? TEXT("true") : TEXT("false"));
	if (IsPowered)
	{
		if (KeySocket && KeySocket->bKeyInserted)
		{
			Ignition();
			if (TrainController)
			{
				TrainController->HasPower = !TrainController->HasPower;

			}
		}
	}
	
	
}
