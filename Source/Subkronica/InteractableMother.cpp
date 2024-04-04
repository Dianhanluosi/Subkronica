// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableMother.h"

// Sets default values
AInteractableMother::AInteractableMother()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableMother::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableMother::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Is Grabbing: %d"), Grabbed);

}

