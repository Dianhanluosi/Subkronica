// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElectricPowerMother.h"
#include "ElectricPowerClick.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API AElectricPowerClick : public AElectricPowerMother
{
	GENERATED_BODY()

public:
	AElectricPowerClick();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Clicked;
	
};
