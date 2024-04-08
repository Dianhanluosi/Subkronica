// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePickUp.h"
#include "PlayerCharacter.h"
#include "Grabber.h"
#include "Camera/CameraComponent.h"

AInteractablePickUp::AInteractablePickUp()
{
}

void AInteractablePickUp::BeginPlay()
{
	Super::BeginPlay();

	RotationPrePickedUp = FRotator(0.f, 0.f, 0.f);
	RotationOffSet = FRotator(0.f, 0.f, 0.f);
}

void AInteractablePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Grabbed)
	{
		Holding();
	}
	else 
	{
		letGo();
	}
	
}

void AInteractablePickUp::Holding()
{

	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	
	if (PlayerController && Player && PlayerCam && RootMeshComponent)
	{
		RootMeshComponent->SetSimulatePhysics(true);
		RootMeshComponent->SetEnableGravity(false);
		RootMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

		FRotator CameraRotation = PlayerCam->GetComponentRotation();
		
		
		if (!PickedUp)
		{
			RootMeshComponent->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));

			RotationPrePickedUp = GetActorRotation();
			RotationOffSet = RotationPrePickedUp - CameraRotation; 
			PickedUp = true;

		}
		
		
		FVector HoldPosition = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * PickUpOffSet;

		FVector Direction = PlayerViewPointLocation - GetActorLocation().GetSafeNormal();

		FHitResult HitResult;
		FVector Start = GetActorLocation();
		FVector End = HoldPosition;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		if (!bHit)
		{
			FVector NewLocation = FMath::VInterpTo(GetActorLocation(), HoldPosition, GetWorld()->GetDeltaSeconds(), MoveSpeed);
			SetActorLocation(NewLocation);
		}
		
		//SetActorLocation(HoldPosition);
		SetActorRotation(CameraRotation + RotationOffSet);
	}
	 
}


void AInteractablePickUp::letGo()
{
	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());

	if (RootMeshComponent)
	{
		RootMeshComponent->SetEnableGravity(true);
		RootMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	}
	
	RotationPrePickedUp = FRotator(0.f, 0.f, 0.f);
	RotationOffSet = FRotator(0.f, 0.f, 0.f);
	PickedUp = false;
}

void AInteractablePickUp::Action()
{
	//UE_LOG(LogTemp, Warning, TEXT("Action!"));

}

void AInteractablePickUp::Shoot()
{
	//UE_LOG(LogTemp, Warning, TEXT("Shoot!"));
	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	if (PlayerController && Player && PlayerCam && RootMeshComponent)
	{
		FVector Direction = PlayerCam->GetForwardVector();
		letGo();
		RootMeshComponent->AddImpulse(Direction * ShootImpulse, NAME_None, true);
	}
	
	
}
