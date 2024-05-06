// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Grabber.h"
#include "Keys.h"

// Sets default values
AKeySocket::AKeySocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UPrimitiveComponent* CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = CollisionComponent;

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKeySocket::OnOverlapBegin);

	KeyHole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyHole"));
	KeyHole->SetupAttachment(RootComponent);

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->SetupAttachment(KeyHole);

}

// Called when the game starts or when spawned
void AKeySocket::BeginPlay()
{
	Super::BeginPlay();

	KeyMesh->SetVisibility(false);
	
}

// Called every frame
void AKeySocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotating && KeyHole)
	{
		
		
		FRotator CurrentHoleRotation = KeyHole->GetRelativeRotation();
		FRotator NewHoleRotation = FMath::RInterpTo(CurrentHoleRotation, EndRotation, DeltaTime, RotationSpeed);
		KeyHole->SetRelativeRotation(NewHoleRotation);
		
		// Check if the rotation is close enough to consider it complete
		if (NewHoleRotation.Equals(EndRotation, 1.f))
		{
			bRotating = false; // Stop rotating
			bKeyInserted = true; // Key is inserted
		}
	}

}

void AKeySocket::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Key = Cast<AKeys>(OtherActor);
	if (Key && !bRotating)
	{
		// Turn off collision for the colliding key
		//Key->SetOwner(this);
		if (FindComponentByClass<UGrabber>() && FindComponentByClass<UGrabber>()->Interactable && Cast<AKeys>(FindComponentByClass<UGrabber>()->Interactable))
		{
			FindComponentByClass<UGrabber>()->Release();
		}
		OnKeyInserted();
		KeyMesh->SetVisibility(true);
		bRotating = true;
		Key->Destroy();

	}
}

