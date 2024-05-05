// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSwitchClick.h"

#include "PowerPlantButtons.h"
#include "PowerPlantSpinner.h"
#include "Components/AudioComponent.h"
#include "PowerPlantButtons.h"

APowerSwitchClick::APowerSwitchClick()
{
	PrimaryActorTick.bCanEverTick = true;

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMesh"));

	RootComponent = SwitchMesh;

}

void APowerSwitchClick::BeginPlay()
{
	Super::BeginPlay();
	AC = FindComponentByClass<UAudioComponent>();
	
}

void APowerSwitchClick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ButtonCount <= 0)
	{
		ButtonCount = 0;
	}
	if (ButtonCount >= Buttons.Num())
	{
		ButtonCount = Buttons.Num();
	}

	if (ButtonCount == Buttons.Num())
	{
		CanBeSwitched = true;
	}
	else
	{
		CanBeSwitched = false;
	}
	
	if (Spinner)
	{
		if (CanBeSwitched)
		{
			if (SwitchedOn)
			{
				Spinner->IsOn = true;
			}
			else
			{
				Spinner->IsOn = false;
			}
		}
		else if (!SwitchedOn)
		{
			Spinner->IsOn = false;
		}
		
	}

	UpdateRotation(DeltaTime);
	
}

void APowerSwitchClick::Action()
{
	Super::Action();

	UE_LOG(LogTemp, Warning, TEXT("Action"));

	
	
	
	SwitchedOn = !SwitchedOn;
	if (!SwitchedOn)
	{
		CanBeSwitched = false;
		for (APowerPlantButtons* Btn: Buttons)
		{
			if (Btn)
			{
				Btn->UnClicked();
			}
		}
	}
	// if (CanBeSwitched)
	// {
	// 	IsOn = !IsOn;
	// }
	//
	 if (AC)
	 {
	 	if (SwitchSound)
	 	{
	 		AC->SetSound(SwitchSound);
	 		AC->Play();
	 	}
	 }

	
}

void APowerSwitchClick::UpdateRotation(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = SwitchedOn? OnRotation : OffRotation;

	float LerpStep = SwitchSpeed * DeltaTime;

	FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, LerpStep);

	SetActorRotation(NewRotation);
}
