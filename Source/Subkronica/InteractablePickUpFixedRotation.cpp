// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePickUpFixedRotation.h"

AInteractablePickUpFixedRotation::AInteractablePickUpFixedRotation()
{
}

void AInteractablePickUpFixedRotation::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractablePickUpFixedRotation::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInteractablePickUpFixedRotation::UpdateRotation(const FRotator& CameraRotation)
{
	//Super::UpdateRotation(CameraRotation);
	// FRotator NewRotation = CameraRotation + FixedRotationOffset;
	// SetActorRotation(NewRotation);

	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());
	if (RootMeshComponent)
	{
		if (!PickedUp)
		{
			// Calculate and store the rotation offset once when first picked up
			RotationPrePickedUp = GetActorRotation();
			RotationOffSet = RotationPrePickedUp - CameraRotation;
			RotationOffSet.Yaw = FixedRotationOffset.Yaw; // Set the fixed yaw offset

			// Preserve the pitch calculation from the original to maintain vertical alignment
			RotationOffSet.Pitch = -RotationOffSet.Pitch; // Invert the pitch component as per original behavior
			RootMeshComponent->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
			PickedUp = true;
		}

		// Adjust camera rotation to account for pitch but use fixed yaw
		FRotator AdjustedCameraRotation = CameraRotation;
		AdjustedCameraRotation.Pitch = -AdjustedCameraRotation.Pitch;
        
		// Apply the fixed yaw and original pitch offset to the adjusted camera's current rotation
		FRotator NewRotation = AdjustedCameraRotation + RotationOffSet;
		NewRotation.Yaw += FixedRotationOffset.Yaw; // Apply the fixed yaw component
		SetActorRotation(NewRotation);
	}
}
