// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "TimerManager.h"
#include "ClickableMother.h"
#include "Components/AudioComponent.h"
#include "ElevatorClick.h"
#include "PowerPlantSpinner.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsMoving = false;  // Initially, the elevator is not moving
	bReadyToMove = true;
	

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	//AC = FindComponentByClass<UAudioComponent>();
	//AC = FindAudioComponentByName(TEXT("AudioComp"));

	AC = FindAudioComponentByName(this, TEXT("Arrival"));
	
}

// Called every frame
void AElevator::Tick(float DeltaTime)
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

	if (!HasPower)
	{
		TargetPositions.Empty();
	}

	if (HasPower)
	{
		MoveTowardsTarget(DeltaTime);

	}
	
	

}

void AElevator::AddTargetPosition(FVector NewPosition, AElevatorClick* NewEC)
{
	if (HasPower)
	{
		if (NewEC)
		{
			TargetPositions.Add(NewPosition);
			EC.Add(NewEC);
		}
	}
	
}


void AElevator::MoveTowardsTarget(float DeltaTime)
{

	// if (TargetPositions.Num() > 0)
	// {
	// 	FVector CurrentPosition = GetActorLocation();
	// 	FVector TargetPosition = TargetPositions[0];
	// 	float Distance = FVector::Dist(CurrentPosition, TargetPosition);
	//
	// 	// Interpolate towards the target position
	// 	FVector NewPosition = FMath::VInterpTo(CurrentPosition, TargetPosition, DeltaTime, Speed);
	// 	SetActorLocation(NewPosition);
	//
	// 	// Check if the elevator is close enough to be considered at the target
	// 	if (Distance < 10.f) // If within 10 units, consider it at the target
	// 		{
	// 		//SetActorLocation(TargetPosition);  // Ensure the position is exactly at the target
	// 		bIsMoving = false;
	// 		GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &AElevator::PauseAtPosition, WaitTime, false);
	//
	// 		// Disable movement until the pause is over
	// 		//bReadyToMove = false;
	//
	// 		// Set a timer to wait before moving to the next target, if any remain
	// 		//if (TargetPositions.Num() > 0)
	// 		//{
	// 		//}
	// 		}
	// 	else
	// 	{
	// 		bIsMoving = true;  // Elevator is moving towards the target
	// 	}
	// }
	
	if (TargetPositions.Num() > 0)
	{
		FVector CurrentPosition = GetActorLocation();
		FVector TargetPosition = TargetPositions[0];
		if (FVector::Dist(CurrentPosition, TargetPosition) < 20.f)
		{
			SetActorLocation(TargetPosition);
			bIsMoving = false;
			TargetPositions.RemoveAt(0);// Remove the reached position
			if (AC && bReadyToMove)
			{
				AC->SetSound(ArriveSound);
				AC->Play();
			}
			if (EC[0])
			{
				EC[0]->IsOn = false;
			}
			EC.RemoveAt(0);
			bReadyToMove = false;  // Set not ready to immediately move to the next target
			// Set a timer to wait before moving to the next target, if any remain
			//if (TargetPositions.Num() > 0)
			//{
				GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &AElevator::PauseAtPosition, WaitTime, false);
			//}
		}
		else if (bReadyToMove)
		{
			//UE_LOG(LogTemp, Warning, TEXT("2"));
			bIsMoving = true;  // Elevator is moving
			FVector Direction = (TargetPosition - CurrentPosition).GetSafeNormal();
			SetActorLocation(CurrentPosition + Direction * Speed * DeltaTime, true);
		}
	}
}

void AElevator::PauseAtPosition()
{
	//TargetPositions.RemoveAt(0);  // Remove the reached target position
	//UE_LOG(LogTemp, Warning, TEXT("1"));
	bReadyToMove = true;  // After the pause, ready to move to the next target
	//bIsMoving = false;   
}

UAudioComponent* AElevator::FindAudioComponentByName(AActor* Actor, const FName& ComponentName)
{
	if (!Actor)
	{
		return nullptr;
	}

	// Iterate through all components of type UAudioComponent
	TArray<UAudioComponent*> Components;
	Actor->GetComponents<UAudioComponent>(Components);
	for (UAudioComponent* Component : Components)
	{
		// Check if the component's name matches the specified name
		if (Component->GetFName() == ComponentName)
		{
			return Component;
		}
	}

	return nullptr; 
}

