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

	virtual void AddTargetPosition (FVector NewPosition);

	UPROPERTY(EditAnywhere)
	float Speed = 100.0f;

	UPROPERTY(EditAnywhere)
	float WaitTime = 5.0f;

private:

	void MoveTowardsTarget (float DeltaTime);

	void PauseAtPosition();

	struct FTimerHandle PauseTimerHandle;

	bool bIsMoving;

};
