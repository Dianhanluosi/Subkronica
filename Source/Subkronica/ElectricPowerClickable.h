// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickableMother.h"
#include "ElectricPowerClickable.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API AElectricPowerClickable : public AClickableMother
{
	GENERATED_BODY()

public:
	AElectricPowerClickable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Action() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AElectricPowerClick* EPC;

	UFUNCTION(BlueprintImplementableEvent)
	void Clicked();
	
};
