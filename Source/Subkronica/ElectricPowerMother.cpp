// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricPowerMother.h"
#include "PowerPlantSpinner.h"

// Sets default values
AElectricPowerMother::AElectricPowerMother()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElectricPowerMother::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElectricPowerMother::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Spinner)
	{
		if (Spinner->IsOn)
		{
			HasPower = true;
		}
		// else
		// {
		// 	HasPower = false;
		// }
	}

}

