// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickableMother.h"
#include "PowerSwitchClick.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API APowerSwitchClick : public AClickableMother
{
	GENERATED_BODY()

public:
	APowerSwitchClick();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Action() override;

	void UpdateRotation(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool CanBeSwitched;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool SwitchedOn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SwitchMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator OffRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator OnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SwitchSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APowerPlantSpinner* Spinner;

	UPROPERTY(EditAnywhere)
	class USoundBase* SwitchSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAudioComponent* AC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class APowerPlantButtons*> Buttons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ButtonCount;
};
