// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricPowerClickable.h"

#include "ElectricPowerMother.h"


AElectricPowerClickable::AElectricPowerClickable()
{
}

void AElectricPowerClickable::BeginPlay()
{
	Super::BeginPlay();
}

void AElectricPowerClickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AElectricPowerClickable::Action()
{
	Clicked();
	if (EPC)
	{
		EPC->IsAlive = !EPC->IsAlive;
	}
}
