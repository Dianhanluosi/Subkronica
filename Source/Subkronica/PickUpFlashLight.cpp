// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpFlashLight.h"
#include "Components/StaticMeshComponent.h"

APickUpFlashLight::APickUpFlashLight()
{
	FlashLightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashLightMesh"));
	RootComponent = FlashLightMesh;
}

void APickUpFlashLight::BeginPlay()
{
	Super::BeginPlay();
}

void APickUpFlashLight::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APickUpFlashLight::Action()
{
	FlashLightSwitch();
}
