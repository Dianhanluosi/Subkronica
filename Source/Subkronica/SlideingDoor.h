// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClickableMother.h"
#include "SlideingDoor.generated.h"

/**
 * 
 */
UCLASS()
class SUBKRONICA_API ASlideingDoor : public AClickableMother
{
	GENERATED_BODY()

public:
	ASlideingDoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Action() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOpen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector OpenLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector CloseLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	class UPrimitiveComponent* CollideBox;

	class UStaticMeshComponent* Door;

	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* OpenSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CloseSound;
	
	
};
