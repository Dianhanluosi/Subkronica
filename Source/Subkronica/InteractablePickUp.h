// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableMother.h"
#include "InteractablePickUp.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API AInteractablePickUp : public AInteractableMother
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AInteractablePickUp();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	virtual void Holding() override;

	virtual void UpdateRotation(const FRotator& CameraRotation);

	virtual void letGo() override;

	virtual void Action() override;
	virtual void Shoot() override;
	

	UPROPERTY(EditDefaultsOnly)
	float PickUpOffSet;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 10;

	UPROPERTY(EditDefaultsOnly)
	float ShootImpulse = 10;
	
	FRotator RotationPrePickedUp;
	FRotator RotationOffSet;
	
};
