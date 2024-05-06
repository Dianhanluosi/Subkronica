// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpSpawner.generated.h"

UCLASS()
class SUBKRONICA_API APickUpSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf <class AInteractableMother> PickUpClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInteractableMother* CurrentPickUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpawnRotationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnWaitTime;

	UFUNCTION(BlueprintCallable)
	void SpawnPickUp();

};
