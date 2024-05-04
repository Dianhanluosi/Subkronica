// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerPlantSpinner.h"

// Sets default values
APowerPlantSpinner::APowerPlantSpinner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpinnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinnerMesh"));

	RootComponent = SpinnerMesh;

}

// Called when the game starts or when spawned
void APowerPlantSpinner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerPlantSpinner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateRotation(DeltaTime);

}

void APowerPlantSpinner::UpdateRotation(float DeltaTime)
{
	float Direction = IsOn? 1.0f : -1.0f;

	RotationSpeed += Direction *= RotationAcceleration * DeltaTime;

	RotationSpeed = FMath::Clamp(RotationSpeed,0.0f, TerminalRotationSpeed);

	IsSpinning  = RotationSpeed != 0.0f;
	
	if (IsSpinning)
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += RotationSpeed * DeltaTime;
		SetActorRotation(NewRotation);
	} 
}

