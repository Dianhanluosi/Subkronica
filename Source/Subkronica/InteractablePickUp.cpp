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
		UpdateRotation(CameraRotation); // This call now handles all rotation-related adjustments

		FVector HoldPosition = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * PickUpOffSet;
		FVector Start = GetActorLocation();
		FVector End = HoldPosition;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		FHitResult HitResult;

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		if (!bHit)
		{
			FVector NewLocation = FMath::VInterpTo(GetActorLocation(), HoldPosition, GetWorld()->GetDeltaSeconds(), MoveSpeed);
			SetActorLocation(NewLocation);
		}
		
		//SetActorLocation(HoldPosition);
		//SetActorRotation(CameraRotation + RotationOffSet);
	}
	 
}

void AInteractablePickUp::UpdateRotation(const FRotator& CameraRotation)
{
	//Original
	// UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	// if (RootMeshComponent && !PickedUp)
	// {
	// 	RootMeshComponent->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	// 	RotationPrePickedUp = GetActorRotation();
	// 	RotationOffSet = RotationPrePickedUp - CameraRotation;
	// 	PickedUp = true;
	// }
	// SetActorRotation(CameraRotation + RotationOffSet);

	//Same same different
	// UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	// if (RootMeshComponent)
	// {
	// 	if (!PickedUp)
	// 	{
	// 		// Calculate and store the rotation offset only once when first picked up
	// 		RotationPrePickedUp = GetActorRotation();
	// 		RotationOffSet = RotationPrePickedUp - CameraRotation;
	// 		RootMeshComponent->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	// 		PickedUp = true;
	// 	}
	//
	// 	// Apply the initial rotation offset to the camera's current rotation
	// 	SetActorRotation(CameraRotation + RotationOffSet);
	// }

	//good
	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	if (RootMeshComponent)
	{
		if (!PickedUp)
		{
			// Calculate and store the rotation offset only once when first picked up
			RotationPrePickedUp = GetActorRotation();
			RotationOffSet = RotationPrePickedUp - CameraRotation;
			RotationOffSet.Pitch = -RotationOffSet.Pitch; // Invert the pitch component immediately
			RootMeshComponent->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
			PickedUp = true;
		}
    
		// Invert the pitch component of the camera rotation before applying the offset
		FRotator AdjustedCameraRotation = CameraRotation;
		AdjustedCameraRotation.Pitch = -AdjustedCameraRotation.Pitch;
        
		// Apply the initial rotation offset to the adjusted camera's current rotation
		SetActorRotation(AdjustedCameraRotation + RotationOffSet);
	}

	//no up and down rotation (global)
	// UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	// if (RootMeshComponent)
	// {
	// 	if (!PickedUp)
	// 	{
	// 		// Calculate and store the rotation offset only once when first picked up
	// 		RotationPrePickedUp = GetActorRotation();
	// 		RotationOffSet = RotationPrePickedUp - CameraRotation;
	// 		RotationOffSet.Pitch = 0; // Lock the pitch offset to maintain the initial pitch
	// 		RootMeshComponent->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	// 		PickedUp = true;
	// 	}
	//
	// 	// Create a new rotation that ignores pitch changes in the camera
	// 	FRotator NewRotation = CameraRotation + RotationOffSet;
	// 	NewRotation.Pitch = RotationPrePickedUp.Pitch; // Use the initial pitch
	//
	// 	// Apply the rotation
	// 	SetActorRotation(NewRotation);
	// }
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
	UE_LOG(LogTemp, Error, TEXT("Action!"));

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
