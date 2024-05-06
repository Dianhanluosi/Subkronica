// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableMother.h"
#include "PlayerCharacter.h"
#include "Grabber.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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
	

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		PlayerCam = Player->FindComponentByClass<UCameraComponent>();
	}

	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());

	if (RootMeshComponent)
	{
		RootMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);

		RootMeshComponent->SetSimulatePhysics(false);
	}

	OriginalZ = GetActorLocation().Z;
	
	
	
}

// Called every frame
void AInteractableMother::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Is Grabbing: %d"), Grabbed);

	if (!Spawnable)
	{
		Bobbing();
	}
	
	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	if (RootMeshComponent && RootMeshComponent->IsSimulatingPhysics())
	{
		Spawnable = true;
	}

	
	

}

void AInteractableMother::Holding()
{
}

void AInteractableMother::letGo()
{
}

void AInteractableMother::Action()
{
}

void AInteractableMother::Shoot()
{
}

void AInteractableMother::Bobbing()
{
	float Time = GetWorld()->GetTimeSeconds();
	float NewZ = OriginalZ + ZBobOffset * FMath::Sin(ZBobSpeed * Time);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z = NewZ;
	SetActorLocation(CurrentLocation);
}

