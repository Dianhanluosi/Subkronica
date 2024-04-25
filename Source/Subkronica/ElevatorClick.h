// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickableMother.h"
#include "ElevatorClick.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API AElevatorClick : public AClickableMother
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AElevatorClick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	void Action() override;
	
};
