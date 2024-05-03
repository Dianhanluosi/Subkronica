// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorClick.h"
#include "Elevator.h"
#include "Components/AudioComponent.h"

AElevatorClick::AElevatorClick()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AElevatorClick::BeginPlay()
{
	Super::BeginPlay();
	AC = FindComponentByClass<UAudioComponent>();

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
		if (AC)
		{
			if (!IsOn)
			{
				AC->SetSound(ClickSound);
				AC->Play();
				ER->AddTargetPosition(ClickPosition, this);
				IsOn = true;
			}
			
		}
		
	}
}
