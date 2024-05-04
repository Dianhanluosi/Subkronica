// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerPlantSpinner.generated.h"

UCLASS()
class SUBKRONICA_API APowerPlantSpinner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerPlantSpinner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSpinning = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SpinnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationAcceleration = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TerminalRotationSpeed = 180.f;

	UFUNCTION(BlueprintCallable)
	void UpdateRotation(float DeltaTime);

};
