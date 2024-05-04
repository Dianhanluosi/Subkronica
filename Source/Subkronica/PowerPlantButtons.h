// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickableMother.h"
#include "PowerPlantButtons.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API APowerPlantButtons : public AClickableMother
{
	GENERATED_BODY()

public:
	APowerPlantButtons();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APowerSwitchClick* Switch;

	void Action() override;

	UFUNCTION(BlueprintCallable)
	virtual void Clicked();

	UFUNCTION(BlueprintCallable)
	virtual void UnClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void ButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void ButtonUnClicked();

	UPROPERTY(EditAnywhere)
	class USoundBase* ClickSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAudioComponent* AC;

	
	
	
};
