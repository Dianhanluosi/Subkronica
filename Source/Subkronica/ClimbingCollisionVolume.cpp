// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbingCollisionVolume.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.h"

// Sets default values
AClimbingCollisionVolume::AClimbingCollisionVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the box component for the blocking volume
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CustomBlockingBox"));
	RootComponent = BoxComponent; // Set it as the root component

	
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel4); 

}

// Called when the game starts or when spawned
void AClimbingCollisionVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClimbingCollisionVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClimbingCollisionVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor); // Cast to APlayerCharacter

	if (PlayerCharacter) // Check if the cast was successful
		{
		PlayerCharacter->IsClimbing = true;
		UE_LOG(LogTemp, Log, TEXT("Overlap with APlayerCharacter detected"));
		}
}

void AClimbingCollisionVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter) // If the overlap ends with APlayerCharacter
		{
		PlayerCharacter->IsClimbing = false;
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		UE_LOG(LogTemp, Log, TEXT("Overlap with APlayerCharacter ended"));
		}
}

