// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"
#include "TimerManager.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsMoving = true;

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		MoveTowardsTarget(DeltaTime);
	
}

void AElevator::AddTargetPosition(FVector NewPosition)
{
	TargetPositions.Add(NewPosition);
}

void AElevator::MoveTowardsTarget(float DeltaTime)
{
	if (TargetPositions.Num() > 0)
	{
		FVector CurrentPosition = GetActorLocation();
		FVector TargetPosition = TargetPositions[0];
		if (FVector::Dist(CurrentPosition, TargetPosition) < 5.f)
		{
			bIsMoving = false;
			TargetPositions.RemoveAt(0);
			GetWorldTimerManager().SetTimer(PauseTimerHandle, this, &AElevator::PauseAtPosition, WaitTime, false);
		}
		else if (bIsMoving)
		{
			FVector Direction = (TargetPosition - CurrentPosition).GetSafeNormal();
			SetActorLocation(CurrentPosition + Direction * Speed * DeltaTime, true);
		}
	}
}

void AElevator::PauseAtPosition()
{
	bIsMoving = true;
}

