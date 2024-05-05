// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractablePickUpFixedRotation.h"
#include "PickUpFlashLight.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API APickUpFlashLight : public AInteractablePickUpFixedRotation
{
	GENERATED_BODY()

public:
	APickUpFlashLight();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void Action() override;

	UFUNCTION(BlueprintImplementableEvent)
	void FlashLightSwitch();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* FlashLightMesh;

	
	
	
};
