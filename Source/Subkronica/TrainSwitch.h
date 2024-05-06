// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickableMother.h"
#include "TrainSwitch.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API ATrainSwitch : public AClickableMother
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APowerPlantSpinner* Spinner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ATrainController* TrainController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ATrainIgnition* Ignition;
	
	void Action() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Switched();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator OffRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator OnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsOn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
	
	
};
