// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableSwitch.h"

AInteractableSwitch::AInteractableSwitch()
{
	PrimaryActorTick.bCanEverTick = true;

	SpinnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinnerMesh"));

	RootComponent = SpinnerMesh;
}

void AInteractableSwitch::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


void AInteractableSwitch::Holding()
{
	Super::Holding();
}

void AInteractableSwitch::letGo()
{
	Super::letGo();
}
