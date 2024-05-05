// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickableMother.h"
#include "Engine/SpotLight.h"
#include "WaterplantWheel.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API AWaterplantWheel : public AClickableMother
{
	GENERATED_BODY()

public:
	AWaterplantWheel();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Action() override;

	void UpdateRotation(float DeltaTime);

	void SelfTurnOff();

	UFUNCTION(BlueprintImplementableEvent)
	void STO();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APowerPlantSpinner* Spinner;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool SwitchedOn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WheelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator OffRotation;

	UPROPERTY(	EditAnywhere, BlueprintReadOnly)
	FRotator OnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SwitchSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class ANiagaraActor*> Waterfalls;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* WaterPlane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class ASpotLight*> CausticsLights;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector WaterPlaneStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector WaterPlaneEnd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool NoWater;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool EnoughWater;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WaterRiseRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WaterFallRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USoundBase* WheelSoundClip1;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// class USoundBase* WheelSoundClip2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAudioComponent* WheelSound;
	

	UAudioComponent* FindAudioComponentByName(AActor* Actor, const FName& ComponentName);
	
};
