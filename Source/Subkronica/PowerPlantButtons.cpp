// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerPlantButtons.h"
#include "PowerSwitchClick.h"
#include "Components/AudioComponent.h"

APowerPlantButtons::APowerPlantButtons()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APowerPlantButtons::BeginPlay()
{
	Super::BeginPlay();
	AC = FindComponentByClass<UAudioComponent>();

}

void APowerPlantButtons::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APowerPlantButtons::Action()
{
	Super::Action();
	Clicked();
}

void APowerPlantButtons::Clicked()
{
	ButtonClicked();

	if (Switch)
	{
		Switch->ButtonCount++;
	}

	if (AC)
	{
		if (ClickSound)
		{
			AC->SetSound(ClickSound);
			AC->Play();
		}
	}

}

void APowerPlantButtons::UnClicked()
{
	ButtonUnClicked();

	if (Switch)
	{
		Switch->ButtonCount--;
	}
	
	if (AC)
	{
		if (ClickSound)
		{
			AC->SetSound(ClickSound);
			AC->Play();
		}
	}

}
