// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideingDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

ASlideingDoor::ASlideingDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollideBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollideBox"));
	RootComponent = CollideBox;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	
}

void ASlideingDoor::BeginPlay()
{
	Super::BeginPlay();
}

void ASlideingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Door)
	{
		FVector TargetLocation = bIsOpen ? OpenLocation : CloseLocation;

		FVector NewLocation = FMath::VInterpTo(Door->GetRelativeLocation(), TargetLocation, DeltaTime, Speed);

		Door->SetRelativeLocation(NewLocation);
	}
	
	
	
}

void ASlideingDoor::Action()
{
	if (bIsOpen)
	{
		AudioComponent->Stop();
		AudioComponent->SetSound(CloseSound);
		AudioComponent->Play();
		bIsOpen = false;
	}else
	{
		AudioComponent->Stop();
		AudioComponent->SetSound(OpenSound);
		AudioComponent->Play();
		bIsOpen = true;
		
	}
	OpenDoor();
}
