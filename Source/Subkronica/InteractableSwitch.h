// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableMother.h"
#include "InteractableSwitch.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API AInteractableSwitch : public AInteractableMother
{
	GENERATED_BODY()

public:
	AInteractableSwitch();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SpinnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator OffRotation = FRotator(-80.f, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator OnRotation = FRotator(50.f, 0, 0);

	float InterpolationWeight = 0.0f;

	float MouseYDelta;
	
	virtual void Holding() override;

	virtual void letGo() override;

	
	
};
