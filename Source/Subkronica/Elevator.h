// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UCLASS()
class SUBKRONICA_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<FVector> TargetPositions;

	UPROPERTY(EditAnywhere)
	TArray<class AElevatorClick*> EC;

	virtual void AddTargetPosition (FVector NewPosition, AElevatorClick* NewEC);

	virtual void MoveTowardsTarget(float DeltaTime);

	virtual void PauseAtPosition();

	UPROPERTY(EditAnywhere)
	float Speed = 100.0f;

	UPROPERTY(EditAnywhere)
	float WaitTime = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere)
	bool bReadyToMove;

	UPROPERTY(EditAnywhere)
	class USoundBase* ArriveSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAudioComponent* AC;

	UAudioComponent* FindAudioComponentByName(AActor* Actor, const FName& ComponentName);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HasPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APowerPlantSpinner* Spinner;
	

private:
	struct FTimerHandle PauseTimerHandle;


};


