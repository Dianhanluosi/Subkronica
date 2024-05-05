// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElectricPowerMother.generated.h"

UCLASS()
class SUBKRONICA_API AElectricPowerMother : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElectricPowerMother();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool HasPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APowerPlantSpinner* Spinner;

};
