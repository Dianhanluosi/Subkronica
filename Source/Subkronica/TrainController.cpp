// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainController.h"
#include "PowerPlantSpinner.h"
#include "Components/StaticMeshComponent.h"
#include "TrainSwitch.h"
#include "TrainIgnition.h"

// Sets default values
ATrainController::ATrainController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ATrainController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

