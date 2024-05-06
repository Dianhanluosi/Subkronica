// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpSpawner.h"
#include "InteractableMother.h"

// Sets default values
APickUpSpawner::APickUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUpSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnTimer = SpawnWaitTime;
	
	SpawnPickUp();
	
}

// Called every frame
void APickUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPickUp && CurrentPickUp->Spawnable)
	{
		CurrentPickUp = nullptr;
	}
	if (!CurrentPickUp)
	{
		SpawnTimer -= DeltaTime;
		if (SpawnTimer <= 0)
		{
			SpawnPickUp();
			SpawnTimer = SpawnWaitTime;
		}
	}

}

void APickUpSpawner::SpawnPickUp()
{
	if (!CurrentPickUp && PickUpClass)
	{

		FVector Location = GetActorLocation();  // Offset by 100 units on X
		//FRotator Rotation = FRotator::ZeroRotator + SpawnRotationOffset;
		FRotator Rotation = GetActorRotation();
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		CurrentPickUp = GetWorld()->SpawnActor<AInteractableMother>(PickUpClass, Location, Rotation, SpawnParams);
	}
}

