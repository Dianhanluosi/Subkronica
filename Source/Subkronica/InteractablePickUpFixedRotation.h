// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractablePickUp.h"
#include "InteractablePickUpFixedRotation.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API AInteractablePickUpFixedRotation : public AInteractablePickUp
{
	GENERATED_BODY()

public:
	AInteractablePickUpFixedRotation();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void UpdateRotation(const FRotator& CameraRotation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator FixedRotationOffset;
	
};
